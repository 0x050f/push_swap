/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/12 17:55:00 by lmartin          ###   ########.fr       */
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

int				order_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_state			*result;
	t_state			*new_states;
	t_state			*states;
	t_state			*actual;
	t_state			*tmp;
	t_instruction	*tmp_instr;
	
	if (!(states = malloc(sizeof(t_state))))
		return (1);
	states->stack_a = copy_stack(stack_a);
	if (!(states->stack_b = malloc(sizeof(t_stack))))
		return (1);
	states->stack_b->max_size = stack_a->max_size;
	states->stack_b->size = 0;
	states->instructions = NULL;
	states->next = NULL;
	result = NULL;
	while (!result)
	{
		new_states = NULL;
		tmp = states;
		while (tmp)
		{
			if (tmp->stack_b->size < 2)
			{
				actual = add_state(&new_states, tmp);
				tmp_instr = add_instruction(&actual->instructions, "pb");
				execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			}
			if (tmp->stack_b->size > 0)
			{
				actual = add_state(&new_states, tmp);
				tmp_instr = add_instruction(&actual->instructions, "pa");
				execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			}
			actual = add_state(&new_states, tmp);
			tmp_instr = add_instruction(&actual->instructions, "sa");
			execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			if (tmp->stack_b->size == 2)
			{
				actual = add_state(&new_states, tmp);
				tmp_instr = add_instruction(&actual->instructions, "sb");
				execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			}
			if (tmp->stack_b->size == 2)
			{
				actual = add_state(&new_states, tmp);
				tmp_instr = add_instruction(&actual->instructions, "ss");
				execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			}
			actual = add_state(&new_states, tmp);
			tmp_instr = add_instruction(&actual->instructions, "ra");
			execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			actual = add_state(&new_states, tmp);
			tmp_instr = add_instruction(&actual->instructions, "rra");
			execute_instructions(tmp_instr, actual->stack_a, actual->stack_b);
			tmp = tmp->next;
		}
		free_states(&states);
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
	free_states(&states);

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
	free_states(&result);
	return (0);
	/*
	size_t			i;
	int				min;
	t_instruction	*tmp;

	min = stack_a->array[0];
	i = 1;
	while (i < stack_a->size)
	{
		if (stack_a->array[i] < min)
			min = stack_a->array[i];
		i++;
	}
	while (is_stack_ordered(stack_a, ASC))
	{
		if (stack_a->array[0] > stack_a->array[1] && stack_a->array[1] != min)
			tmp = add_instruction(instr, "sa");
		else
			tmp = add_instruction(instr, "ra");
		execute_instructions(tmp, stack_a, stack_b);
	}*/
}

void			resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t		mvt[2];
	size_t		min[2];
	size_t		min_mvt[2];
	t_instruction	*tmp;

	while (stack_a->size > 5)
	{
		if (can_pb(stack_a, stack_b))
			tmp = add_instruction(instr, "pb");
		else
		{
			mvt[0] = closer_pos_to_inf(stack_a->array[0], stack_b);
			min[0] = get_less_mvt_at_begin(mvt[0], &min_mvt[0], stack_a, stack_b);
			min[1] = get_less_mvt_at_end(mvt[0], &min_mvt[1], stack_a, stack_b);
			if (mvt[0] > stack_b->size / 2)
				mvt[1] = stack_b->size - mvt[0];
			else
				mvt[1] = mvt[0];
			if (stack_a->size > 1 && (min[0] <= mvt[1] || min[1] <= mvt[1]))
			{
				if (min[0] <= min[1] && min_mvt[0] <= stack_b->size / 2)
					tmp = add_instruction(instr, "rr");
				else if (min[0] < min[1] && min_mvt[0] > stack_b->size / 2)
					tmp = add_instruction(instr, "ra");
				else if (min_mvt[1] > stack_b->size / 2)
					tmp = add_instruction(instr, "rrr");
				else
					tmp = add_instruction(instr, "rra");
			}
			else if (mvt[0] > stack_b->size / 2)
				tmp = add_instruction(instr, "rrb");
			else
				tmp = add_instruction(instr, "rb");
		}
		execute_instructions(tmp, stack_a, stack_b);
	}
	order_a(stack_a, stack_b, instr);
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
	while (is_stack_ordered(stack_a, ASC))
	{
		tmp = add_instruction(instr, "rra");
		execute_instructions(tmp, stack_a, stack_b);
	}
	/*
	align_stack_b(stack_a, stack_b, instr);
	while (stack_b->size)
	{
		tmp = add_instruction(instr, "pa");
		execute_instructions(tmp, stack_a, stack_b);
	}*/
}

int				main(int argc, char *argv[])
{
	t_stack				stack_a;
	t_stack				stack_b;
	t_instruction		*instr;

	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	if (DEBUG)
		print_stacks(&stack_a, &stack_b);
	instr = NULL;
	resolve(&stack_a, &stack_b, &instr);
	print_instructions(instr);
	return (0);
}
