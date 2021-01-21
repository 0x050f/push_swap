/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/21 12:10:12 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			align_stack_b(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t	i;
	size_t	num;
	t_instruction	*tmp;

	i = 0;
	num = 0;
	if (is_stack_ordered(stack_b, DESC))
	{
		while (i < stack_b->size - 1 &&
stack_b->array[i] > stack_b->array[i + 1])
			i++;
		if (i > stack_b->size / 2)
			num = stack_b->size - (i + 1);
		else
			num = i + 1;
	}
	while (num--)
	{
		if (i > stack_b->size / 2)
			tmp = add_instruction(instr, "rrb");
		else
			tmp = add_instruction(instr, "rb");
		execute_instructions(tmp, stack_a, stack_b);
	}
}

void			align_stack_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t	i;
	size_t	num;
	t_instruction	*tmp;

	i = 0;
	num = 0;
	if (is_stack_ordered(stack_a, ASC))
	{
		while (i < stack_a->size - 1 &&
stack_a->array[i] < stack_a->array[i + 1])
			i++;
		if (i > stack_b->size / 2)
			num = stack_a->size - (i + 1);
		else
			num = i + 1;
	}
	while (num--)
	{
		if (i > stack_b->size / 2)
			tmp = add_instruction(instr, "rra");
		else
			tmp = add_instruction(instr, "ra");
		execute_instructions(tmp, stack_a, stack_b);
	}
}

void			bruteforce_choice_a(t_state **new_states, t_state *tmp, size_t i, size_t num, t_stack *stack_b)
{
	t_instruction	*tmp_instr;

	if (tmp->stack_b->size < 2 && (!tmp->last_instr ||
ft_strcmp(tmp->last_instr->line, "pa")))
		new_state_instruction(new_states, tmp, "pb");
	if (tmp->stack_b->size > 0 && (!tmp->last_instr ||
ft_strcmp(tmp->last_instr->line, "pb")))
		new_state_instruction(new_states, tmp, "pa");
	if (!tmp->last_instr || (ft_strcmp(tmp->last_instr->line, "sa") &&
ft_strcmp(tmp->last_instr->line, "sb") &&
ft_strcmp(tmp->last_instr->line, "ss")))
		new_state_instruction(new_states, tmp, "sa");
	if (tmp->stack_b->size > 1 && (!tmp->last_instr ||
(ft_strcmp(tmp->last_instr->line, "sb") &&
ft_strcmp(tmp->last_instr->line, "sa") &&
ft_strcmp(tmp->last_instr->line, "ss"))))
		new_state_instruction(new_states, tmp, "sb");
	if (tmp->stack_b->size > 1 && (!tmp->last_instr ||
(ft_strcmp(tmp->last_instr->line, "sb") &&
ft_strcmp(tmp->last_instr->line, "sa") &&
ft_strcmp(tmp->last_instr->line, "ss"))))
		new_state_instruction(new_states, tmp, "ss");
	tmp_instr = tmp->last_instr;
	size_t j;
	j = 0;
	while (j < tmp->stack_a->size / 2 && tmp_instr && ft_strcmp(tmp_instr->line, "ra"))
	{
		tmp_instr = tmp->last_instr->prev;
		j++;
	}
	if (!tmp->last_instr || (ft_strcmp(tmp->last_instr->line, "rra") && j < tmp->stack_a->size / 2))
	{
		if (i <= stack_b->size / 2 && num && !tmp->stack_b->size)
		{
			num--;
			new_state_instruction(new_states, tmp, "rr");
		}
		else
			new_state_instruction(new_states, tmp, "ra");
	}
	tmp_instr = tmp->last_instr;
	j = 0;
	while (j < tmp->stack_a->size / 2 && tmp_instr && ft_strcmp(tmp_instr->line, "rra"))
	{
		tmp_instr = tmp->last_instr->prev;
		j++;
	}
	if (!tmp->last_instr || (ft_strcmp(tmp->last_instr->line, "ra") && j < tmp->stack_a->size / 2))
	{
		if (i > stack_b->size / 2 && num && !tmp->stack_b->size)
		{
			num--;
			new_state_instruction(new_states, tmp, "rrr");
		}
		else
			new_state_instruction(new_states, tmp, "rra");
	}
}

int				bruteforce_order_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_state			*result;
	t_state			*new_states;
	t_state			*states;
	t_state			*tmp;
	t_instruction	*tmp_instr;
	

	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	if (is_stack_ordered(stack_b, DESC))
	{
		while (i < stack_b->size - 1 &&
stack_b->array[i] > stack_b->array[i + 1])
			i++;
		if (i > stack_b->size / 2)
			num = stack_b->size - (i + 1);
		else
			num = i + 1;
	}
	if (!(states = new_empty_state(stack_a, NULL, stack_a->max_size)))
		return (1);
	result = NULL;
	while (!result)
	{
		new_states = NULL;
		tmp = states;
		while (tmp)
		{
			bruteforce_choice_a(&new_states, tmp, i, num, stack_b);
			tmp = tmp->next;
		}
		free_states(states);
		states = new_states;
		tmp = states;
		while (tmp)
		{
			if (!tmp->stack_b->size && !is_stack_ordered(tmp->stack_a, ASC))
			{
				add_state(&result, tmp);
				break;
			}
			tmp = tmp->next;
		}
	}
	free_states(states);
	execute_instructions(result->instructions, stack_a, stack_b);
	tmp_instr = *instr;
	if (tmp_instr)
	{
		while (tmp_instr->next)
			tmp_instr = tmp_instr->next;
		tmp_instr->next = copy_instructions(result->instructions);
		((t_instruction *)tmp_instr->next)->prev = tmp_instr;
	}
	else
		*instr = copy_instructions(result->instructions);
	free_states(result);
	return (0);
}

int				create_states_resolution(t_state	**states)
{
	int				i;
	t_instruction	*tmp;
	t_state			*new_state;

	new_state = new_state_instruction(states, *states, "pb");
	tmp = NULL;
	i = -DEPTH + 1;
	while (++i < DEPTH)
	{
		if (i < 0)
		{
			new_state = new_state_instruction(states, *states, "ra");
			tmp = add_n_instructions(&new_state->instructions, "ra",
DEPTH + (i - 1));
			execute_instructions(tmp, new_state->stack_a, new_state->stack_b);
		}
		else if (i > 0)
		{
			new_state = new_state_instruction(states, *states, "rra");
			tmp = add_n_instructions(&new_state->instructions, "rra", i - 1);
			execute_instructions(tmp, new_state->stack_a, new_state->stack_b);
		}
		else if (i != -DEPTH)
			new_state = new_state_instruction(states, *states, "rra");
		if (!new_state)
			return (1);
	}
	return (0);
}

t_instruction		*rotate(t_state *state)
{
	t_instruction		*instr;
	size_t				mvt[2];
	size_t				min[2];
	size_t				min_mvt[2];

	mvt[0] = closer_pos_to_inf(state->stack_a->array[0],
state->stack_b);
	min[0] = get_less_mvt_at_begin(mvt[0], &min_mvt[0], state->stack_a,
state->stack_b);
	min[1] = get_less_mvt_at_end(mvt[0], &min_mvt[1], state->stack_a,
state->stack_b);
	if (mvt[0] > state->stack_b->size / 2)
		mvt[1] = state->stack_b->size - mvt[0];
	else
		mvt[1] = mvt[0];
	if (state->stack_a->size > 1 && (min[0] <= mvt[1] || min[1] <= mvt[1]))
	{
		if (min[0] <= min[1] && min_mvt[0] <= state->stack_b->size / 2)
			instr = add_instruction(&state->instructions, "rr");
		else if (min[0] < min[1] && min_mvt[0] > state->stack_b->size / 2)
			instr = add_instruction(&state->instructions, "ra");
		else if (min_mvt[1] > state->stack_b->size / 2)
			instr = add_instruction(&state->instructions, "rrr");
		else
			instr = add_instruction(&state->instructions, "rra");
	}
	else if (mvt[0] > state->stack_b->size / 2)
		instr = add_instruction(&state->instructions, "rrb");
	else
		instr = add_instruction(&state->instructions, "rb");
	return (instr);
}

int				resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_instruction	*tmp;
	t_state			*states;
	t_state			*tmp_state;

	if (!(states = new_empty_state(stack_a, stack_b, stack_a->max_size)))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	tmp_state = states;
	if (stack_a->size > 5)
	{
		if (create_states_resolution(&states))
		{
			write(STDERR_FILENO, "Error\n", 6);
			return (1);
		}
		tmp_state = states->next;
	}
	while (tmp_state)
	{
		while (tmp_state->stack_a->size > 5)
		{
			if (can_pb(tmp_state->stack_a, tmp_state->stack_b))
				tmp = add_instruction(&tmp_state->instructions, "pb");
			else
				tmp = rotate(tmp_state);
			if (!tmp)
			{
				free_states(states);
				write(STDERR_FILENO, "Error\n", 6);
				return (1);
			}
			execute_instructions(tmp, tmp_state->stack_a, tmp_state->stack_b);
		}
		tmp_state = tmp_state->next;
	}
	t_state		*solution;

	solution = states->next;
	if (solution)
		tmp_state = solution->next;
	else
	{
		tmp_state = NULL;
		solution = states;
	}
	while (tmp_state)
	{
		if (count_instructions(tmp_state->instructions) < count_instructions(solution->instructions))
			solution = tmp_state;
		tmp_state = tmp_state->next;
	}
	if (solution->instructions)
	{
		execute_instructions(solution->instructions, stack_a, stack_b);
		*instr = copy_instructions(solution->instructions);
	}
	free_states(states);
	bruteforce_order_a(stack_a, stack_b, instr);
	if (stack_b->size > 1)
		align_stack_b(stack_a, stack_b, instr);
	while (stack_b->size)
	{
		if (stack_b->array[0] > stack_a->array[stack_a->size - 1] ||
(stack_b->array[0] < stack_a->array[0] &&
stack_a->array[0] < stack_a->array[stack_a->size - 1]))
			tmp = add_instruction(instr, "pa");
		else
			tmp = add_instruction(instr, "rra");
		execute_instructions(tmp, stack_a, stack_b);
	}
	align_stack_a(stack_a, stack_b, instr);
	return (0);
}

int				main(int argc, char *argv[])
{
	t_stack				stack_a;
	t_stack				stack_b;
	t_instruction		*instr;

	if (argc < 2)
		return (0);
	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	if (DEBUG)
		print_stacks(&stack_a, &stack_b);
	instr = NULL;
	if (is_stack_ordered(&stack_a, ASC) && resolve(&stack_a, &stack_b, &instr))
	{
		free_instructions(instr);
		return (1);
	}
	print_instructions(instr);
	free_instructions(instr);
	return (0);
}
