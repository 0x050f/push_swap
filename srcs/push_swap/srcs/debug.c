/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:36:10 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/24 11:06:48 by lmartin          ###   ########.fr       */
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
** Print both stacks
*/

void			print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	size_t	i;
	size_t	max_size;

	max_size = stack_a->size;
	if (stack_b->size > stack_a->size)
		max_size = stack_b->size;
	write(STDOUT_FILENO, _YELLOW, ft_strlen(_YELLOW));
	write(STDOUT_FILENO, "stacks\n", 7);
	write(STDOUT_FILENO, _END, ft_strlen(_END));
	i = -1;
	while (++i < max_size)
	{
		write(STDOUT_FILENO, "	", 1);
		if ((int)(stack_a->size - max_size + i) >= 0)
			ft_putnbr(stack_a->array[stack_a->size - max_size + i]);
		else
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, " ", 1);
		if ((int)(stack_b->size - max_size + i) >= 0)
			ft_putnbr(stack_b->array[stack_b->size - max_size + i]);
		else
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, "\n", 1);
	}
	write(STDOUT_FILENO, "	_ _\n	a b\n", 10);
}
