/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/09 05:56:11 by lmartin          ###   ########.fr       */
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

void			resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t		i;
	t_instruction	*tmp;

	i = 0;
	while (stack_a->size)
	{
		if (can_pb(stack_a, stack_b))
			tmp = add_instruction(instr, "pb");
		else
		{
			tmp = add_instruction(instr, "rb");
		}
		execute_instructions(tmp, stack_a, stack_b);
		if (DEBUG)
		{
			print_instructions(tmp);
			print_stacks(stack_a, stack_b);
		}
		i++;
	}
	while (is_stack_ordered(stack_b, DESC))
	{
		tmp = add_instruction(instr, "rb");
		execute_instructions(tmp, stack_a, stack_b);
		if (DEBUG)
		{
			print_instructions(tmp);
			print_stacks(stack_a, stack_b);
		}
	}
	while (stack_b->size)
	{
		tmp = add_instruction(instr, "pa");
		execute_instructions(tmp, stack_a, stack_b);
		if (DEBUG)
		{
			print_instructions(tmp);
			print_stacks(stack_a, stack_b);
		}
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
	t_instruction		*instr;

	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	if (DEBUG)
		print_stacks(&stack_a, &stack_b);
	instr = NULL;
	resolve(&stack_a, &stack_b, &instr);
	print_instructions(instr);
	return (0);
}
