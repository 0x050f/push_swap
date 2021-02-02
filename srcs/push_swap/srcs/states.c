/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:31:31 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/24 12:23:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_state			*new_state_instruction(t_state **states, t_state *old_state,
char *line)
{
	t_state			*state;
	t_instruction	*instr;

	if (!(state = add_state(states, old_state)))
		return (NULL);
	if (!(instr = add_instruction(&state->instructions, line)))
	{
		free_states(state);
		return (NULL);
	}
	state->last_instr = instr;
	execute_instructions(instr, state->stack_a, state->stack_b, 0);
	return (state);
}

void			free_states(t_state *states)
{
	t_state			*tmp;
	t_state			*next;

	tmp = states;
	while (tmp)
	{
		next = tmp->next;
		free_stack(tmp->stack_a);
		free_stack(tmp->stack_b);
		free_instructions(tmp->instructions);
		free(tmp);
		tmp = next;
	}
}

t_state			*add_state(t_state **states, t_state *state_from)
{
	t_state		*tmp;
	t_state		*new;

	if (!(new = malloc(sizeof(t_state))))
		return (NULL);
	new->stack_a = NULL;
	new->stack_b = NULL;
	new->instructions = NULL;
	new->last_instr = NULL;
	new->next = NULL;
	if (!(new->stack_a = copy_stack(state_from->stack_a)) ||
!(new->stack_b = copy_stack(state_from->stack_b)) || (state_from->instructions
	&& !(new->instructions = copy_instructions(state_from->instructions))))
	{
		free_states(new);
		return (NULL);
	}
	tmp = *states;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*states = new;
	return (new);
}

t_state			*new_empty_state(t_stack *stack_a, t_stack *stack_b,
size_t max_size)
{
	t_state		*state;

	if (!(state = malloc(sizeof(t_state))))
		return (NULL);
	if (stack_a)
		state->stack_a = copy_stack(stack_a);
	else if (!(state->stack_a = new_empty_stack(max_size)))
	{
		free(state);
		return (NULL);
	}
	if (stack_b)
		state->stack_b = copy_stack(stack_b);
	else if (!(state->stack_b = new_empty_stack(max_size)))
	{
		free_stack(state->stack_a);
		free(state);
		return (NULL);
	}
	state->instructions = NULL;
	state->last_instr = NULL;
	state->next = NULL;
	return (state);
}
