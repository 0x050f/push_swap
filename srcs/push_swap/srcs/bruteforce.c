/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 12:42:53 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/23 12:57:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				check_bruteforce_solution(t_state *states, t_state **result)
{
	while (states && !(*result))
	{
		if (!states->stack_b->size && !is_stack_ordered(states->stack_a, ASC))
		{
			if (!add_state(result, states))
				return (1);
		}
		states = states->next;
	}
	return (0);
}

t_state			*pick_bruteforce_solution(t_state *states, size_t pos[2],
t_stack *stack_b)
{
	t_state			*result;
	t_state			*new_states;
	t_state			*tmp;

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
				return (NULL);
			}
			tmp = tmp->next;
		}
		free_states(states);
		states = new_states;
		if (check_bruteforce_solution(states, &result))
			return (NULL);
	}
	return (result);
}

int				bruteforce_order_a(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t			pos[2];
	t_state			*result;
	t_state			*states;

	calcul_align_b(&pos[0], &pos[1], stack_b);
	if (!(states = new_empty_state(stack_a, NULL, stack_a->max_size)))
		return (1);
	if (!(result = pick_bruteforce_solution(states, pos, stack_b)))
	{
		free_states(states);
		return (1);
	}
	execute_instructions(result->instructions, stack_a, stack_b);
	if (!copy_and_concat_instructions(instr, result->instructions))
	{
		free_states(result);
		return (1);
	}
	free_states(result);
	return (0);
}
