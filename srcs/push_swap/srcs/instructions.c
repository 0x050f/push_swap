/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/11 15:49:41 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			print_instructions(t_instruction *instr)
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

void			execute_instructions(t_instruction *instr,
t_stack *stack_a, t_stack *stack_b)
{
	if (DEBUG)
		print_instructions(instr);
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
	if (DEBUG)
		print_stacks(stack_a, stack_b);
}

void			remove_instruction(t_instruction **instructions,
t_instruction *to_delete)
{
	if (*instructions == to_delete)
	{
		if (to_delete->prev)
			*instructions = to_delete->prev;
		else if (to_delete->next)
			*instructions = to_delete->next;
		else
			*instructions = NULL;
	}
	else
	{
		if (to_delete->prev)
			((t_instruction *)to_delete->prev)->next = to_delete->next;
		if (to_delete->next)
			((t_instruction *)to_delete->next)->prev = to_delete->prev;
	}
	free(to_delete->line);
	free(to_delete);
}

/*
** Add instruction with line
*/

t_instruction	*add_instruction(t_instruction **instructions, char *line)
{
	t_instruction *tmp;
	t_instruction *new;

	if (!(new = malloc(sizeof(t_instruction))))
		return (NULL);
	new->line = ft_strdup(line);
	new->prev = NULL;
	new->next = NULL;
	tmp = *instructions;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		new->prev = tmp;
		tmp->next = new;
	}
	else
		*instructions = new;
	return (new);
}
