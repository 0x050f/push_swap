/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/11 03:12:35 by lmartin          ###   ########.fr       */
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
	while (i > 0 && stack_a->size - i < minimal_mvt)
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

void			resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t		i;
	size_t		mvt[2];
	size_t		min[2];
	size_t		min_mvt[2];
	t_instruction	*tmp;

	i = 0;
	while (stack_a->size)
	{
		if (can_pb(stack_a, stack_b))
			tmp = add_instruction(instr, "pb");
		else
		{
			mvt[0] = closer_pos_to_inf(stack_a->array[0], stack_b);
			min[0] = get_less_mvt_at_begin(mvt[0], &min_mvt[0], stack_a, stack_b);
			min[1] = get_less_mvt_at_end(mvt[0], &min_mvt[1], stack_a, stack_b);
			if (mvt[0] > stack_b->size / 2)
				mvt[1] = stack_b->size - mvt[0];
			else
				mvt[1] = mvt[0];
			if (stack_a->size > 1 && (min[0] < mvt[1] || min[1] < mvt[1]))
			{
				// RA OR RRA
				if (min[0] < min[1] && min_mvt[0] > stack_b->size / 2)
					tmp = add_instruction(instr, "ra");
				else if (min[0] < min[1])
					tmp = add_instruction(instr, "rr");
				else if (min_mvt[1] > stack_b->size / 2)
					tmp = add_instruction(instr, "rrr");
				else
					tmp = add_instruction(instr, "rra");
			}
			else if (mvt[0] > stack_b->size / 2)
				tmp = add_instruction(instr, "rrb");
			else
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
	size_t	j;
	size_t	num;

	j = 0;
	num = 0;
	if (is_stack_ordered(stack_b, DESC))
	{
		while (j < stack_b->size - 1 &&
stack_b->array[j] > stack_b->array[j + 1])
			j++;
		if (j > stack_b->size / 2)
			num = stack_b->size - (j + 1);
		else
			num = j + 1;
	}
	while (num--)
	{
		if (j > stack_b->size / 2)
			tmp = add_instruction(instr, "rrb");
		else
			tmp = add_instruction(instr, "rb");
		execute_instructions(tmp, stack_a, stack_b);
		if (DEBUG)
		{
			print_instructions(tmp);
			print_stacks(stack_a, stack_b);
		}
		i++;
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
