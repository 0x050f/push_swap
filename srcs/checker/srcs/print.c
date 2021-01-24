/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:28:05 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/24 15:28:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void			print_bottom_stack(int max_size_nbr[2])
{
	write(STDOUT_FILENO, "	", 1);
	write_n_char(max_size_nbr[0], '_');
	write(STDOUT_FILENO, " ", 1);
	write_n_char(max_size_nbr[1], '_');
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "	", 1);
	write_n_char(max_size_nbr[0] - 1, ' ');
	write(STDOUT_FILENO, "a ", 2);
	write_n_char(max_size_nbr[1] - 1, ' ');
	write(STDOUT_FILENO, "b", 1);
	write(STDOUT_FILENO, "\n", 1);
}

void			print_numbers_stacks(int max_size, int max_size_nbr[2],
t_stack *stack_a, t_stack *stack_b)
{
	int		i;

	i = -1;
	while (++i < max_size)
	{
		write(STDOUT_FILENO, "	", 1);
		if ((int)(stack_a->size - max_size + i) >= 0)
			write_n_char(max_size_nbr[0] -
size_nbr(stack_a->array[stack_a->size - max_size + i]), ' ');
		if ((int)(stack_a->size - max_size + i) >= 0)
			ft_putnbr(stack_a->array[stack_a->size - max_size + i]);
		else
			write_n_char(max_size_nbr[0], ' ');
		write(STDOUT_FILENO, " ", 1);
		if ((int)(stack_b->size - max_size + i) >= 0)
			write_n_char(max_size_nbr[1] -
size_nbr(stack_b->array[stack_b->size - max_size + i]), ' ');
		if ((int)(stack_b->size - max_size + i) >= 0)
			ft_putnbr(stack_b->array[stack_b->size - max_size + i]);
		else
			write_n_char(max_size_nbr[1], ' ');
		write(STDOUT_FILENO, "\n", 1);
	}
}

/*
** Print both stacks
*/

void			print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int		max_size_nbr[2];
	int		max_size;

	max_size = stack_a->size;
	if (stack_b->size > stack_a->size)
		max_size = stack_b->size;
	write(STDOUT_FILENO, _YELLOW, ft_strlen(_YELLOW));
	write(STDOUT_FILENO, "stacks\n", 7);
	write(STDOUT_FILENO, _END, ft_strlen(_END));
	max_size_nbr[0] = get_max_size_nbr_stack(stack_a);
	max_size_nbr[1] = get_max_size_nbr_stack(stack_b);
	print_numbers_stacks(max_size, max_size_nbr, stack_a, stack_b);
	print_bottom_stack(max_size_nbr);
}

/*
** Print all instructions
*/

void			print_instructions(t_instruction *instructions)
{
	write(STDOUT_FILENO, _YELLOW, ft_strlen(_YELLOW));
	write(STDOUT_FILENO, "instructions\n", 13);
	write(STDOUT_FILENO, _END, ft_strlen(_END));
	while (instructions)
	{
		write(STDOUT_FILENO, "	", 1);
		write(STDOUT_FILENO, instructions->line, ft_strlen(instructions->line));
		write(STDOUT_FILENO, "\n", 1);
		instructions = instructions->next;
	}
}

/*
** Print debug after 1 instruction
*/

void			print_debug_instruction(t_instruction *instr,
t_stack *stack_a, t_stack *stack_b)
{
	write(STDOUT_FILENO, "---\n", 4);
	write(STDOUT_FILENO, _YELLOW, ft_strlen(_YELLOW));
	write(STDOUT_FILENO, "do	", 3);
	write(STDOUT_FILENO, _END, ft_strlen(_END));
	write(STDOUT_FILENO, instr->line, ft_strlen(instr->line));
	write(STDOUT_FILENO, "\n", 1);
	print_stacks(stack_a, stack_b);
}
