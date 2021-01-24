/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/24 12:20:58 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Choose that to do
*/

void			execute_instructions(t_instruction *instr, t_stack *stack_a,
t_stack *stack_b, int debug)
{
	while (instr)
	{
		if (debug)
			print_instruction(instr);
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
		if (debug)
			print_stacks(stack_a, stack_b);
		instr = instr->next;
	}
}

t_instruction	*copy_and_concat_instructions(t_instruction **instr,
t_instruction *new)
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

t_instruction	*copy_instructions(t_instruction *instructions)
{
	t_instruction	*new;

	new = NULL;
	while (instructions)
	{
		if (!(add_instruction(&new, instructions->line)))
		{
			free_instructions(new);
			return (NULL);
		}
		instructions = instructions->next;
	}
	return (new);
}

/*
** Add n instructions of line
*/

t_instruction	*add_n_instructions(t_instruction **instructions, char *line,
size_t n)
{
	t_instruction	*start;

	start = NULL;
	if (n > 0)
	{
		if (!(start = add_instruction(instructions, line)))
			return (NULL);
		n--;
		while (n > 0)
		{
			if (!(add_instruction(instructions, line)))
			{
				free_instructions(start);
				return (NULL);
			}
			n--;
		}
	}
	return (start);
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
	if (!(new->line = ft_strdup(line)))
	{
		free(new);
		return (NULL);
	}
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
