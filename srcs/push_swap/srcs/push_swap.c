/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/23 11:29:07 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			calcul_align_b(size_t *pos, size_t *mvt, t_stack *stack_b)
{
	*pos = 0;
	*mvt = 0;
	if (is_stack_ordered(stack_b, DESC))
	{
		while (*pos < stack_b->size - 1 &&
stack_b->array[*pos] > stack_b->array[*pos + 1])
			(*pos)++;
		if (*pos > stack_b->size / 2)
			*mvt = stack_b->size - (*pos + 1);
		else
			*mvt = *pos + 1;
	}
}

int				align_stack_b(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t	i;
	size_t	num;
	t_instruction	*tmp;

	calcul_align_b(&i, &num, stack_b);
	while (num--)
	{
		if (i > stack_b->size / 2)
			tmp = add_instruction(instr, "rrb");
		else
			tmp = add_instruction(instr, "rb");
		if (!tmp)
			return (1);
		execute_instructions(tmp, stack_a, stack_b);
	}
	return (0);
}

int				align_stack_a(t_stack *stack_a, t_stack *stack_b,
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
		if (!tmp)
			return (1);
		execute_instructions(tmp, stack_a, stack_b);
	}
	return (0);
}

int				reverse_rotate_bruteforce_a(t_state **new_states, t_state *tmp,
size_t pos[2], t_stack *stack_b)
{
	size_t			j;
	t_instruction	*tmp_instr;

	tmp_instr = tmp->last_instr;
	j = 0;
	while (j++ < tmp->stack_a->size / 2 && tmp_instr &&
(!ft_strcmp(tmp_instr->line, "rra") || !ft_strcmp(tmp_instr->line, "rrr")))
		tmp_instr = tmp->last_instr->prev;
	if (!tmp->last_instr || ((ft_strcmp(tmp->last_instr->line, "ra") && ft_strcmp(tmp->last_instr->line, "rr") && j < tmp->stack_a->size / 2)))
	{
		if (pos[0] > stack_b->size / 2 && !tmp->stack_b->size && pos[1])
		{
			pos[1]--;
			if (!new_state_instruction(new_states, tmp, "rrr"))
				return (1);
		}
		else if (!new_state_instruction(new_states, tmp, "rra"))
			return (1);
	}
	return (0);
}

int				rotate_bruteforce_a(t_state **new_states, t_state *tmp,
size_t pos[2], t_stack *stack_b)
{
	size_t			j;
	t_instruction	*tmp_instr;

	tmp_instr = tmp->last_instr;
	j = 0;
	while (j++ < tmp->stack_a->size / 2 && tmp_instr &&
(!ft_strcmp(tmp_instr->line, "ra") || !ft_strcmp(tmp_instr->line, "rr")))
		tmp_instr = tmp->last_instr->prev;
	if (!tmp->last_instr || ((ft_strcmp(tmp->last_instr->line, "rra") && ft_strcmp(tmp->last_instr->line, "rrr") && j < tmp->stack_a->size / 2)))
	{
		if (pos[0] <= stack_b->size / 2 && !tmp->stack_b->size && pos[1])
		{
			pos[1]--;
			if (!new_state_instruction(new_states, tmp, "rr"))
				return (1);
		}
		else if (!new_state_instruction(new_states, tmp, "ra"))
			return (1);
	}
	return (0);
}

int				bruteforce_choice_a(t_state **new_states, t_state *tmp,
size_t pos[2], t_stack *stack_b)
{
	if (tmp->stack_b->size < 2 && (!tmp->last_instr ||
ft_strcmp(tmp->last_instr->line, "pa")) &&
!new_state_instruction(new_states, tmp, "pb"))
		return (1);
	if (tmp->stack_b->size > 0 && (!tmp->last_instr ||
ft_strcmp(tmp->last_instr->line, "pb")) &&
!new_state_instruction(new_states, tmp, "pa"))
		return (1);
	if (!tmp->last_instr || (ft_strcmp(tmp->last_instr->line, "sa") &&
ft_strcmp(tmp->last_instr->line, "sb") &&
ft_strcmp(tmp->last_instr->line, "ss")))
	{
		if (!new_state_instruction(new_states, tmp, "sa"))
			return (1);
		if (tmp->stack_b->size > 1 &&
!new_state_instruction(new_states, tmp, "sb"))
			return (1);
		if (tmp->stack_b->size > 1 &&
!new_state_instruction(new_states, tmp, "ss"))
			return (1);
	}
	if (rotate_bruteforce_a(new_states, tmp, pos, stack_b))
		return (1);
	if (reverse_rotate_bruteforce_a(new_states, tmp, pos, stack_b))
		return (1);
	return (0);
}

t_instruction		*copy_and_concat_instructions(t_instruction **instr, t_instruction *new)
{
	t_instruction	*ptr;
	t_instruction	*tmp_instr;

	tmp_instr = *instr;
	if (tmp_instr)
	{
		while (tmp_instr->next)
			tmp_instr = tmp_instr->next;
		if (!(tmp_instr->next = copy_instructions(new)))
			return (NULL);
		ptr = tmp_instr->next;
		((t_instruction *)tmp_instr->next)->prev = tmp_instr;
	}
	else
	{
		*instr = copy_instructions(new);
		ptr = *instr;
	}
	return (ptr);
}

int				bruteforce_order_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_state			*result;
	t_state			*new_states;
	t_state			*states;
	t_state			*tmp;
	size_t	pos[2];

	calcul_align_b(&pos[0], &pos[1], stack_b);
	if (!(states = new_empty_state(stack_a, NULL, stack_a->max_size)))
		return (1);
	result = NULL;
	while (!result)
	{
		new_states = NULL;
		tmp = states;
		while (tmp)
		{
			if (bruteforce_choice_a(&new_states, tmp, pos, stack_b))
			{
				free_states(new_states);
				return (1);
			}
			tmp = tmp->next;
		}
		free_states(states);
		states = new_states;
		tmp = states;
		while (tmp)
		{
			if (!tmp->stack_b->size && !is_stack_ordered(tmp->stack_a, ASC))
			{
				if (!add_state(&result, tmp))
					return (1);
				break;
			}
			tmp = tmp->next;
		}
	}
	free_states(states);
	execute_instructions(result->instructions, stack_a, stack_b);
	if (!copy_and_concat_instructions(instr, result->instructions))
	{
		free_states(result);
		return (1);
	}
	free_states(result);
	return (0);
}

int				create_states_resolution(t_state	**states)
{
	int				i;
	t_instruction	*tmp;
	t_state			*new;

	i = -DEPTH - 1;
	while (++i < DEPTH)
	{
		tmp = NULL;
		if (!i)
			new = new_state_instruction(states, *states, "pb");
		else if (i < 0)
		{
			new = new_state_instruction(states, *states, "ra");
			tmp = add_n_instructions(&new->instructions, "ra", DEPTH + i);
		}
		else if (i > 0)
		{
			new = new_state_instruction(states, *states, "rra");
			tmp = add_n_instructions(&new->instructions, "rra", i - 1);
		}
		execute_instructions(tmp, new->stack_a, new->stack_b);
		if (!new || (!tmp && i && i != -DEPTH && i != 1))
			return (1);
	}
	return (0);
}

t_instruction		*rotate_a(t_state *stt, size_t min[2], size_t min_mvt[2])
{
	t_instruction		*instr;

	if (min[0] <= min[1] && min_mvt[0] <= stt->stack_b->size / 2)
		instr = add_instruction(&stt->instructions, "rr");
	else if (min[0] < min[1] && min_mvt[0] > stt->stack_b->size / 2)
		instr = add_instruction(&stt->instructions, "ra");
	else if (min_mvt[1] > stt->stack_b->size / 2)
		instr = add_instruction(&stt->instructions, "rrr");
	else
		instr = add_instruction(&stt->instructions, "rra");
	return (instr);
}

t_instruction		*rotate(t_state *stt)
{
	t_instruction		*instr;
	size_t				mvt[2];
	size_t				min[2];
	size_t				min_mvt[2];

	mvt[0] = closer_pos_to_inf(stt->stack_a->array[0], stt->stack_b);
	min[0] = less_mvt_at_begin(mvt[0], &min_mvt[0], stt->stack_a, stt->stack_b);
	min[1] = less_mvt_at_end(mvt[0], &min_mvt[1], stt->stack_a, stt->stack_b);
	if (mvt[0] > stt->stack_b->size / 2)
		mvt[1] = stt->stack_b->size - mvt[0];
	else
		mvt[1] = mvt[0];
	if (stt->stack_a->size > 1 && (min[0] <= mvt[1] || min[1] <= mvt[1]))
		instr = rotate_a(stt, min, min_mvt);
	else if (mvt[0] > stt->stack_b->size / 2)
		instr = add_instruction(&stt->instructions, "rrb");
	else
		instr = add_instruction(&stt->instructions, "rb");
	return (instr);
}

int				large_resolve(t_state *states)
{
	t_instruction	*tmp;
	t_state			*tmp_state;

	tmp_state = states->next;
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
				return (1);
			}
			execute_instructions(tmp, tmp_state->stack_a, tmp_state->stack_b);
		}
		tmp_state = tmp_state->next;
	}
	return (0);
}

int				pick_solution(t_state *states, t_stack *stack_a,
t_stack *stack_b, t_instruction **instr)
{
	t_state			*solution;
	t_state			*tmp_state;

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
		if (!(*instr = copy_instructions(solution->instructions)))
		{
			free_states(states);
			write(STDERR_FILENO, "Error\n", 6);
			return (1);
		}
	}
	return (0);
}

int				realign_and_fill_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_instruction	*tmp;

	if (stack_b->size > 1 && align_stack_b(stack_a, stack_b, instr))
		return (1);
	while (stack_b->size)
	{
		if (stack_b->array[0] > stack_a->array[stack_a->size - 1] ||
(stack_b->array[0] < stack_a->array[0] &&
stack_a->array[0] < stack_a->array[stack_a->size - 1]))
			tmp = add_instruction(instr, "pa");
		else
			tmp = add_instruction(instr, "rra");
		if (!tmp)
			return (1);
		execute_instructions(tmp, stack_a, stack_b);
	}
	if (align_stack_a(stack_a, stack_b, instr))
		return (1);
	return (0);
}

int				resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_state			*states;

	if (!(states = new_empty_state(stack_a, stack_b, stack_a->max_size)))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	if (stack_a->size > 5)
	{
		if (create_states_resolution(&states) || large_resolve(states))
		{
			write(STDERR_FILENO, "Error\n", 6);
			return (1);
		}
	}
	pick_solution(states, stack_a, stack_b, instr);
	free_states(states);
	if (bruteforce_order_a(stack_a, stack_b, instr))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	if (realign_and_fill_a(stack_a, stack_b, instr))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
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
