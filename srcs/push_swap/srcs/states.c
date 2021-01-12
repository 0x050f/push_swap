/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:31:31 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/12 17:28:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		free_states(t_state **states)
{
	t_instruction	*tmp_instr;
	t_state			*tmp;
	t_state			*next;
	
	tmp = *states;
	while (tmp)
	{
		next = tmp->next;
		free_stack(tmp->stack_a);
		tmp->stack_a = NULL;
		free_stack(tmp->stack_b);
		tmp->stack_b = NULL;
		tmp_instr = tmp->instructions;
		while (tmp_instr)
		{
			tmp->instructions = tmp->instructions->next;
			free(tmp_instr->line);
			free(tmp_instr);
			tmp_instr = tmp->instructions;
		}
		tmp->instructions = NULL;
		tmp->next = NULL;
		tmp = next;
	}
	*states = NULL;
}

t_state		*add_state(t_state **states, t_state *state_from)
{
	t_state		*tmp;
	t_state		*new;

	if (!(new = malloc(sizeof(t_state))))
		return (NULL);
	new->stack_a = copy_stack(state_from->stack_a);
	new->stack_b = copy_stack(state_from->stack_b);
	new->instructions = copy_instructions(state_from->instructions);
	new->next = NULL;
	tmp = *states;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*states = new;
	return (new);
}
