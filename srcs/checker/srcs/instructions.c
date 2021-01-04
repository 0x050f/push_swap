/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:11:04 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/04 17:24:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** Add instruction with line
*/
int			add_instruction(t_instruction **instructions, char *line)
{
	t_instruction *tmp;
	t_instruction *new;

	if (!(new = malloc(sizeof(t_instruction))))
		return (1);
	new->line = line;
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
		if (read(STDIN_FILENO, line + 3, 1) < 0 || line[3] != '\n')
			return (-1);
		line[3] = '\0';
	}
	else
		line[2] = '\0';
	if (line != "sa" && line != "sb" && line != "ss" && line != "pa" &&
line != "pb" && line != "ra" && line != "rb" && line != "rr" && line != "rra" &&
line != "rrb" && line != "rrr")
		return (-1);
	if (add_instruction(instructions, line))
		return (-1);
	return (1);
}
