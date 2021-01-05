/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 01:53:21 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		execute_instructions(t_instruction *instr,
t_stack *stack_a, t_stack *stack_b)
{
	while (instr)
	{
		if (instr->line[0] == 's')
		{
			if (instr->line[1] == 'a' || instr->line[1] == 's')
				swap_stack(stack_a);
			if (instr->line[1] == 'b' || instr->line[1] == 's')
				swap_stack(stack_b);
		}
		else if (!ft_strcmp(instr->line, "pa"))
			push_stack(stack_a, stack_b);
		else if (!ft_strcmp(instr->line, "pb"))
			push_stack(stack_b, stack_a);
		else if (instr->line[0] == 'r')
		{
			if (!ft_strcmp(instr->line, "ra") || !ft_strcmp(instr->line, "rr"))
				rotate_stack(stack_a);
			if (!ft_strcmp(instr->line, "rb") || !ft_strcmp(instr->line, "rr"))
				rotate_stack(stack_b);
			if (!ft_strcmp(instr->line, "rra") || !ft_strcmp(instr->line, "rrr"))
				reverse_rotate_stack(stack_a);
			if (!ft_strcmp(instr->line, "rrb") || !ft_strcmp(instr->line, "rrr"))
				reverse_rotate_stack(stack_b);
		}
		if (DEBUG)
		{
			print_instructions(instr);
			print_stacks(stack_a, stack_b);
		}
		instr = instr->next;
	}
}

/*
** Add instruction with line
*/
int			add_instruction(t_instruction **instructions, char *line)
{
	t_instruction *tmp;
	t_instruction *new;

	if (!(new = malloc(sizeof(t_instruction))))
		return (1);
	new->line = ft_strdup(line);
	new->next = NULL;
	tmp = *instructions;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*instructions = new;
	return (0);
}

/*
** Get instruction from STDIN then add_instruction
** if no more input is available return 0, return negative number if fail and
** positive one otherwise
*/
int				get_instruction(t_instruction **instructions)
{
	int		ret;
	char	line[4];

	if ((ret = read(STDIN_FILENO, line, 3)) <= 0)
		return (ret);
	if (line[2] != '\n')
	{
		if (line[0] == '\n' || line[1] == '\n')
			return (-1);
		if (read(STDIN_FILENO, line + 3, 1) < 0 || line[3] != '\n')
			return (-1);
		line[3] = '\0';
	}
	else
		line[2] = '\0';
	if (ft_strcmp(line, "sa") && ft_strcmp(line, "sb") &&
ft_strcmp(line, "ss") && ft_strcmp(line, "pa") && ft_strcmp(line, "pb") &&
ft_strcmp(line, "ra") && ft_strcmp(line, "rb") && ft_strcmp(line, "rr") &&
ft_strcmp(line, "rra") && ft_strcmp(line, "rrb") && ft_strcmp(line, "rrr"))
		return (-1);
	if (add_instruction(instructions, line))
		return (-1);
	return (1);
}
