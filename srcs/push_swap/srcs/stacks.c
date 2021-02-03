/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:18 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/03 00:58:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Return 0 if the stack is ordered otherwise return 1
*/

int				is_stack_ordered(t_stack *stack, int order)
{
	size_t	i;

	i = 0;
	while (i < stack->size - 1)
	{
		if ((order == ASC && stack->array[i] >= stack->array[i + 1])
			|| (order == DESC && stack->array[i] <= stack->array[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

/*
** Check if the stack contains the given number.
*/

int				stack_contains(t_stack *stack, int num)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->array[i++] == num)
			return (1);
	}
	return (0);
}

/*
** Copy a stack
*/

t_stack			*copy_stack(t_stack *stack)
{
	size_t		i;
	t_stack		*new;

	if (!(new = malloc(sizeof(t_stack))))
		return (NULL);
	if (!(new->array = malloc(sizeof(int) * stack->max_size)))
		return (NULL);
	i = 0;
	while (i < stack->size)
	{
		new->array[i] = stack->array[i];
		i++;
	}
	new->size = stack->size;
	new->max_size = stack->max_size;
	return (new);
}

t_stack			*new_empty_stack(size_t max_size)
{
	t_stack		*stack;

	if (!(stack = malloc(sizeof(t_stack))))
		return (NULL);
	if (!(stack->array = malloc(sizeof(int) * max_size)))
	{
		free(stack);
		return (NULL);
	}
	stack->max_size = max_size;
	stack->size = 0;
	return (stack);
}
