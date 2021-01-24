/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:36:10 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/24 14:02:03 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			write_n_char(int n, char c)
{
	while (n-- > 0)
		write(STDOUT_FILENO, &c, 1);
}

int				size_nbr(int n)
{
	long	nnbr;
	int		size;

	size = 0;
	nnbr = n;
	if (nnbr < 0)
	{
		size = 1;
		nnbr *= -1;
	}
	if (nnbr != 0)
	{
		if (nnbr / 10 > 0)
			size += size_nbr(nnbr / 10);
		size++;
		return (size);
	}
	if (n == 0)
		size++;
	return (size);
}

int				get_max_size_nbr_stack(t_stack *stack)
{
	int		size;
	size_t	i;

	if (!stack->size)
		size = 1;
	else
		size = size_nbr(stack->array[0]);
	i = 1;
	while (i < stack->size)
	{
		if (size < size_nbr(stack->array[i]))
			size = size_nbr(stack->array[i]);
		i++;
	}
	return (size);
}
