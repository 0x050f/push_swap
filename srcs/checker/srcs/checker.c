/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:28:53 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/04 18:45:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/* ******************************* DEBUG ************************************ */

#include <stdio.h>

void			print_stacks(t_stack *stack_a, t_stack *stack_b)
{
	size_t	i;
	size_t  max_size;

	max_size = stack_a->size;
	if (stack_b->size > stack_a->size)
		max_size = stack_b->size;
	i = 0;
	printf("TOP\n");
	while (i < max_size)
	{
		if ((int)(stack_a->size - max_size + i) >= 0)
			printf("%d", stack_a->array[stack_a->size - max_size + i]);
		else
			printf(" ");
		printf(" ");
		if ((int)(stack_b->size - max_size + i) >= 0)
			printf("%d", stack_b->array[stack_b->size - max_size + i]);
		else
			printf(" ");
		printf("\n");
		i++;
	}
	printf("_ _\n");
	printf("a b\n");
}

void			print_instructions(t_instruction *instructions)
{
	printf("INSTRUCTIONS\n");
	while (instructions)
	{
		printf("%s\n", instructions->line);
		instructions = instructions->next;
	}
}

/* ************************************************************************** */

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
** atoi passing a pointer to the number in parameter and returning 1 if there is
** an error (not a number or not a integer)
*/
int				ft_atoi(const char *str, int *num)
{
	char	*ptr;
	long	nbr;
	int		sign;
	size_t	i;

	ptr = (char *)str;
	nbr = 0;
	sign = 1;
	if (*ptr == '-' && ptr++)
		sign *= -1;
	i = 0;
	while (*ptr >= '0' && *ptr <= '9' && i++ < 9)
		nbr = nbr * 10 + *ptr++ - '0';
	if (*ptr != '\0' || nbr > 2147483647 || nbr < -2147483648)
		return (1);
	*num = nbr * sign;
	return (0);
}

int				main(int argc, char *argv[])
{
	size_t	i;
	int		num;
	t_stack	stack_a;
	t_stack stack_b;

	if (!(stack_a.array = malloc(sizeof(int) * (argc - 1))) ||
!(stack_b.array = malloc(sizeof(int) * (argc - 1))))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	stack_a.size = 0;
	stack_b.size = 0;
	i = 1;
	while (i < (size_t)argc && !(ft_atoi(argv[i], &num)) &&
!(stack_contains(&stack_a, num)))
	{
		stack_a.array[i++ - 1] = num;
		stack_a.size++;
	}
	if (i != (size_t)argc)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	int					ret;
	t_instruction		*instructions;

	instructions = NULL;
	ret = get_instruction(&instructions);
	while (ret > 0)
		ret = get_instruction(&instructions);
	if (ret < 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	printf("%zu\n", stack_b.size);
	print_instructions(instructions);
	print_stacks(&stack_a, &stack_b);
	execute_instructions(instructions, &stack_a, &stack_b);
	if (is_stack_ordered(&stack_a) || stack_b.size)
		write(STDOUT_FILENO, "KO\n", 3);
	else
		write(STDOUT_FILENO, "OK\n", 3);
	return (0);
}
