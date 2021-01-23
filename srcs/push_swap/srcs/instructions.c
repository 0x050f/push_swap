/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/23 12:49:03 by lmartin          ###   ########.fr       */
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

size_t			count_instructions(t_instruction *instr)
{
	size_t nb;

	nb = 0;
	while (instr)
	{
		nb++;
		instr = instr->next;
	}
	return (nb);
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

void			free_instructions(t_instruction *instructions)
{
	t_instruction	*next;

	while (instructions)
	{
		next = instructions->next;
		free(instructions->line);
		free(instructions);
		instructions = next;
	}
}

t_instruction		*copy_and_concat_instructions(t_instruction **instr,
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
