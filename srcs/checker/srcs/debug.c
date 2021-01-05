/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:36:10 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 01:47:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void			print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	size_t	i;
	size_t  max_size;

	max_size = stack_a->size;
	if (stack_b->size > stack_a->size)
		max_size = stack_b->size;
	write(STDOUT_FILENO, "stacks\n", 7);
	i = 0;
	while (i < max_size)
	{
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
		i++;
	}
	write(STDOUT_FILENO, "_ _\n", 4);
	write(STDOUT_FILENO, "a b\n", 4);
}

void			print_instructions(t_instruction *instructions)
{
	write(STDOUT_FILENO, "instructions\n", 13);
	while (instructions)
	{
		write(STDOUT_FILENO, instructions->line, ft_strlen(instructions->line));
		write(STDOUT_FILENO, "\n", 1);
		instructions = instructions->next;
	}
}
