/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/07 00:15:54 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		print_instructions(t_instruction *instr)
{
	while (instr)
	{
		write(STDOUT_FILENO, instr->line, ft_strlen(instr->line));
		write(STDOUT_FILENO, "\n", 1);
		instr = instr->next;
	}
}

/*
** Choose that to do
*/

void		execute_instructions(t_instruction *instr,
t_stack *stack_a, t_stack *stack_b)
{
	while (instr)
	{
		if (!ft_strcmp(instr->line, "sa") || !ft_strcmp(instr->line, "ss"))
			swap_stack(stack_a);
		if (!ft_strcmp(instr->line, "sb") || !ft_strcmp(instr->line, "ss"))
			swap_stack(stack_b);
		if (!ft_strcmp(instr->line, "pa"))
			push_stack(stack_a, stack_b);
		if (!ft_strcmp(instr->line, "pb"))
			push_stack(stack_b, stack_a);
		if (!ft_strcmp(instr->line, "ra") || !ft_strcmp(instr->line, "rr"))
			rotate_stack(stack_a);
		if (!ft_strcmp(instr->line, "rb") || !ft_strcmp(instr->line, "rr"))
			rotate_stack(stack_b);
		if (!ft_strcmp(instr->line, "rra") || !ft_strcmp(instr->line, "rrr"))
			reverse_rotate_stack(stack_a);
		if (!ft_strcmp(instr->line, "rrb") || !ft_strcmp(instr->line, "rrr"))
			reverse_rotate_stack(stack_b);
		instr = instr->next;
	}
}

/*
** Add instruction with line
*/

t_instruction		*add_instruction(t_instruction **instructions, char *line)
{
	t_instruction *tmp;
	t_instruction *new;

	if (!(new = malloc(sizeof(t_instruction))))
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	tmp = *instructions;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*instructions = new;
	return (new);
}
