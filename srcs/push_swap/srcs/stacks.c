/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:18 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/08 10:58:28 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			free_stack(t_stack *stack)
{
	free(stack->array);
	free(stack);
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
