/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:28:53 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/13 01:09:47 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

/*
** Read and fill intructions chained list
*/

#include <string.h>

int				init_instructions(t_instruction **instructions)
{
	int		errno;
	int		ret;

	errno = 0;
	*instructions = NULL;
	ret = get_instruction(instructions);
	while (ret > 0)
		ret = get_instruction(instructions);
	if (ret < 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	t_stack				stack_a;
	t_stack				stack_b;
	t_instruction		*instructions;

	if (argc < 2)
		return (0);
	if (init_stacks(argc, argv, &stack_a, &stack_b))
		return (1);
	if (init_instructions(&instructions))
		return (1);
	if (DEBUG)
	{
		print_instructions(instructions);
		print_stacks(&stack_a, &stack_b);
	}
	execute_instructions(instructions, &stack_a, &stack_b);
	if (is_stack_ordered(&stack_a) || stack_b.size)
		write(STDOUT_FILENO, "KO\n", 3);
	else
		write(STDOUT_FILENO, "OK\n", 3);
	return (0);
}
