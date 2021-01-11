/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:58:17 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/11 15:45:24 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Return 1 if pb is possible to fit with all values in stack_b
** otherwise return 0
*/

int				can_pb(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_a->size)
		return (0);
	if (stack_b->size < 2)
		return (1);
	else if (stack_a->array[0] > stack_b->array[0])
	{
		if (stack_a->array[0] < stack_b->array[stack_b->size - 1] &&
stack_b->array[0] < stack_b->array[stack_b->size - 1])
			return (1);
		else if (stack_a->array[0] > stack_b->array[stack_b->size - 1] &&
stack_b->array[0] > stack_b->array[stack_b->size - 1])
			return (1);
	}
	else if (stack_a->array[0] < stack_b->array[stack_b->size - 1] &&
stack_b->array[stack_b->size - 1] < stack_b->array[0])
		return (1);
	return (0);
}

/*
** Return the closest pos of a number inferior of 'nb', return the position of
** the next number to the smallest in stack
*/

size_t			closer_pos_to_inf(int nb, t_stack *stack)
{
	size_t		pos;

	pos = 0;
	if (nb > stack->array[0] && nb < stack->array[stack->size - 1])
		return (pos);
	while (pos < stack->size && nb > stack->array[pos])
		pos++;
	if (pos == stack->size)// > all
	{
		pos = 1;
		while (pos < stack->size && stack->array[pos - 1] > stack->array[pos])
			pos++;
		if (pos == stack->size)
			pos = 0;
		return (pos);
	}
	while (pos < stack->size - 1 && nb < stack->array[pos])
		pos++;
	if (pos == stack->size - 1 && stack->array[pos] > nb)// < all
	{
		pos = 1;
		while (pos < stack->size && stack->array[pos - 1] > stack->array[pos])
			pos++;
		if (pos == stack->size)
			pos = 0;
	}
	return (pos);
}

/*
** Calcul if a number on range from the beginning of minimal_movement has less
** movement needed to store in stack_b
*/

size_t			get_less_mvt_at_begin(size_t minimal_mvt, size_t *min_mvt,
t_stack *stack_a, t_stack *stack_b)
{
	size_t		i;
	size_t		min;
	size_t		tmp[2];

	if (minimal_mvt > stack_b->size / 2)
		minimal_mvt = stack_b->size - minimal_mvt;
	min = minimal_mvt + 1;
	i = 1;
	while (i < stack_a->size && i < minimal_mvt)
	{
		tmp[0] = closer_pos_to_inf(stack_a->array[i], stack_b);
		tmp[1] = stack_b->size - tmp[0];
		if (tmp[0] > stack_b->size / 2 && i + tmp[1] < min)
		{
			min = i + tmp[1];
			*min_mvt = tmp[0];
		}
		else if (tmp[0] >= i && tmp[0] < min)
		{
			min = tmp[0];
			*min_mvt = tmp[0];
		}
		else if (tmp[0] < i && i < min)
		{
			min = i;
			*min_mvt = tmp[0];
		}
		i++;
	}
	return (min);
}

/*
** Calcul if a number on range from the end of minimal_movement has less
** movement needed to store in stack_b
*/

size_t			get_less_mvt_at_end(size_t minimal_mvt, size_t *min_mvt,
t_stack *stack_a, t_stack *stack_b)
{
	size_t		i;
	size_t		min;
	size_t		tmp[2];

	if (minimal_mvt > stack_b->size / 2)
		minimal_mvt = stack_b->size - minimal_mvt;
	min = minimal_mvt + 1;
	i = stack_a->size - 1;
	while (i > 0 && (stack_a->size - i) < minimal_mvt)
	{
		tmp[0] = closer_pos_to_inf(stack_a->array[i], stack_b);
		tmp[1] = stack_b->size - tmp[0];
		if (tmp[0] > stack_b->size / 2 &&
tmp[1] >= (stack_a->size - i) && tmp[1] < min)
		{
			min = tmp[1];
			*min_mvt = tmp[0];
		}
		else if (tmp[0] > stack_b->size / 2 &&
tmp[1] < (stack_a->size - i) && (stack_a->size - i) < min)
		{
			min = (stack_a->size - i);
			*min_mvt = tmp[0];
		}
		else if ((stack_a->size - i) + tmp[0] < min)
		{
			min = (stack_a->size - i) + tmp[0];
			*min_mvt = tmp[0];
		}
		i--;
	}
	return (min);
}
