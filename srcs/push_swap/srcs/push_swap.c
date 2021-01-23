/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/23 12:55:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				pick_solution(t_state *states, t_stack *stack_a,
t_stack *stack_b, t_instruction **instr)
{
	t_state			*solution;
	t_state			*tmp_state;

	solution = states->next;
	tmp_state = NULL;
	if (solution)
		tmp_state = solution->next;
	else
		solution = states;
	while (tmp_state)
	{
		if (count_instructions(tmp_state->instructions) <
count_instructions(solution->instructions))
			solution = tmp_state;
		tmp_state = tmp_state->next;
	}
	if (solution->instructions)
	{
		execute_instructions(solution->instructions, stack_a, stack_b);
		if (!(*instr = copy_instructions(solution->instructions)))
		{
			free_states(states);
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
		return (1);
	if (stack_a->size > 5 &&
(create_states_resolution(&states) || large_resolve(states)))
		return (1);
	if (pick_solution(states, stack_a, stack_b, instr))
		return (1);
	free_states(states);
	if (bruteforce_order_a(stack_a, stack_b, instr))
		return (1);
	if (realign_and_fill_a(stack_a, stack_b, instr))
		return (1);
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
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	print_instructions(instr);
	free_instructions(instr);
	return (0);
}
