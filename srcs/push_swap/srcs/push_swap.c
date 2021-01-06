/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 07:52:19 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/06 18:00:39 by lmartin          ###   ########.fr       */
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

int				need_swap_a(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * 1 0 | a
	 *
	 * or
	 *
	 * 1 0 2 .. | a
	*/
	(void)stack_b;
	return ((stack_a->size == 2 ||
(stack_a->size > 2 && stack_a->array[1] < stack_a->array[2]))
&& stack_a->array[0] > stack_a->array[1]);
}

int				need_swap_b(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * 0 1 .. | b
	*/
	(void)stack_a;
	return (stack_b->size > 2 && stack_b->array[0] < stack_b->array[1]);
}

int				need_pb(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * 2 1 0 .. | a
	 * | b
	*/
	return (stack_a->size &&
!stack_b->size &&
stack_a->array[0] > stack_a->array[1] &&
stack_a->array[1] > stack_a->array[2]);
}

int				need_pa(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * | a
	 * 1 .. | b
	 *
	 * or
	 *
	 * 1 .. | a
	 * 0 .. | b
	 *
	 * or
	 *
	 * 0 1 | a
	 * 2 .. | b
	*/
	return (stack_b->size && (!stack_a->size ||
(stack_b->array[0] < stack_a->array[0] ||
 stack_b->array[0] > stack_a->array[stack_a->size - 1])));
}

void			resolve(t_stack *stack_a, t_stack *stack_b)
{
	int		i;

	i = 0;
	while ((stack_b->size || is_stack_ordered(stack_a)) && i < 20)
	{
		if (need_swap_a(stack_a, stack_b)) // sa ?
		{
			swap_stack(stack_a);
			if (need_swap_b(stack_a, stack_b)) // sb ?
			{
				swap_stack(stack_b);
				write(STDOUT_FILENO, "ss\n", 3);
			}
			else
			{
				write(STDOUT_FILENO, "sa\n", 3);
			}
		}
		else if (need_swap_b(stack_a, stack_b)) // sb ?
		{
			swap_stack(stack_b);
			write(STDOUT_FILENO, "sb\n", 3);
		}
		else if (stack_a->size > 2 && stack_a->array[0] < stack_a->array[1] && stack_a->array[0] < stack_a->array[stack_a->size - 1] && stack_a->array[1] > stack_a->array[stack_a->size - 1])
		{
			push_stack(stack_b, stack_a);
			write(STDOUT_FILENO, "pb\n", 3);
		}
		else if (stack_a->size > 2 &&
(stack_a->array[0] > stack_a->array[2] ||
stack_a->array[0] > stack_a->array[stack_a->size - 1])) // ra ?
		{
			rotate_stack(stack_a);
			write(STDOUT_FILENO, "ra\n", 3);
		}
		else if (stack_a->size > 2 && stack_a->array[stack_a->size - 1] < stack_a->array[1]) // rra
		{
			reverse_rotate_stack(stack_a);
			write(STDOUT_FILENO, "rra\n", 4);
		}
		else if (need_pb(stack_a, stack_b)) // pb ?
		{
			push_stack(stack_b, stack_a);
			write(STDOUT_FILENO, "pb\n", 3);
		}
		else if (need_pa(stack_a, stack_b)) // pa ?
		{
			push_stack(stack_a, stack_b);
			write(STDOUT_FILENO, "pa\n", 3);
		}
		else if (!stack_b->size) // pb ?
		{
			push_stack(stack_b, stack_a);
			write(STDOUT_FILENO, "pb\n", 3);
		}
		if (DEBUG)
			print_stacks(stack_a, stack_b);
		i++;
	}
	if (DEBUG)
	{
		write(STDOUT_FILENO, "Nombre de d'operations: ", 24);
		ft_putnbr(i);
		write(STDOUT_FILENO, "\n", 1);
	}
}

int				main(int argc, char *argv[])
{
	t_stack				stack_a;
	t_stack				stack_b;

	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	if (DEBUG)
		print_stacks(&stack_a, &stack_b);
	resolve(&stack_a, &stack_b);
	return (0);
}
