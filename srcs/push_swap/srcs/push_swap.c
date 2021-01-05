/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 07:52:19 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 18:35:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Return 0 if the stack is ordered otherwise return 1
*/

int				is_stack_ordered(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->size - 1)
	{
		if (stack->array[i] >= stack->array[i + 1])
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

void			resolve(t_stack *stack_a, t_stack *stack_b)
{
	int i;

	i = 0;
	while ((stack_b->size || is_stack_ordered(stack_a)) && i < 20)
	{
		if (stack_a->size > 1 && (stack_a->array[0] > stack_a->array[1]) &&
(stack_a->size < 4 || (stack_a->size > 2 &&
stack_a->array[1] < stack_a->array[2] &&
stack_a->array[2] > stack_a->array[0])))
		{
			swap_stack(stack_a);
			write(STDOUT_FILENO, "sa\n", 4);
		}
		else if (stack_a->size > 2 && (stack_a->array[1] < stack_a->array[0]
|| stack_a->array[0] > stack_a->array[stack_a->size - 1]))
		{
			if (stack_a->array[1] < stack_a->array[stack_a->size - 1])
			{
				rotate_stack(stack_a);
				write(STDOUT_FILENO, "ra\n", 3);
			}
			else
			{
				reverse_rotate_stack(stack_a);
				write(STDOUT_FILENO, "rra\n", 4);
			}
		}
		else if (!stack_a->size || (stack_b->size &&
stack_b->array[0] < stack_a->array[0] && (stack_a->size < 3 ||
stack_a->array[1] < stack_a->array[2])))
		{
			push_stack(stack_a, stack_b);
			write(STDOUT_FILENO, "pa\n", 3);
		}
		else if (!stack_b->size || (stack_a->size &&
stack_a->array[0] > stack_b->array[0]))
		{
			push_stack(stack_b, stack_a);
			write(STDOUT_FILENO, "pb\n", 3);
		}
		print_stacks(stack_a, stack_b);
		i++;
	}
}

int				main(int argc, char *argv[])
{
	t_stack				stack_a;
	t_stack				stack_b;

	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	print_stacks(&stack_a, &stack_b);
	resolve(&stack_a, &stack_b);
	return (0);
}
