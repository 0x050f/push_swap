/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:18 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/19 18:21:21 by lmartin          ###   ########.fr       */
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

/*
** Allocate arrays of stacks and initiate stack_a with args
*/

int				init_stacks(int argc, char *argv[],
t_stack *stack_a, t_stack *stack_b)
{
	size_t		i;
	int			num;

	if (!(stack_a->array = malloc(sizeof(int) * (argc - 1))) ||
!(stack_b->array = malloc(sizeof(int) * (argc - 1))))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	stack_a->max_size = argc - 1;
	stack_b->max_size = argc - 1;
	stack_a->size = 0;
	stack_b->size = 0;
	i = 1;
	while (i < (size_t)argc && !(ft_atoi(argv[i], &num)) &&
!(stack_contains(stack_a, num)))
	{
		stack_a->array[i++ - 1] = num;
		stack_a->size++;
	}
	if (i != (size_t)argc)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}
