/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/08 17:27:01 by lmartin          ###   ########.fr       */
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

int				need_swap_a(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * 1 0 .. | a
	*/
	(void)stack_b;
	return (stack_a->size > 1 && stack_a->array[0] > stack_a->array[1] &&
(stack_a->size == 2 || stack_a->array[0] < stack_a->array[2]));
}

int				need_swap_b(t_stack *stack_a, t_stack *stack_b)
{
	/*
	 * 0 1 .. | b
	*/
	(void)stack_a;
	return (stack_b->size > 1 && stack_b->array[0] < stack_b->array[1]);
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

t_instruction	*choose_instruction(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	t_instruction	*new;
	t_instruction	*tmp;
	t_stack			*copy_a;
	t_stack			*copy_b;

	new = NULL;
	if (need_swap_a(stack_a, stack_b)) // sa ?
	{
		if (need_swap_b(stack_a, stack_b)) // sb ?
			new = add_instruction(instr, "ss");
		else
			new = add_instruction(instr, "sa");
	}
	else if (need_swap_b(stack_a, stack_b)) // sb ?
		new = add_instruction(instr, "sb");
	else if (stack_a->size > 2 && stack_a->array[0] < stack_a->array[1] && stack_a->array[0] < stack_a->array[stack_a->size - 1] && stack_a->array[1] > stack_a->array[stack_a->size - 1])
		new = add_instruction(instr, "pb");
	else if (stack_a->size > 2 &&
(stack_a->array[0] > stack_a->array[2] ||
stack_a->array[0] > stack_a->array[stack_a->size - 1])) // ra ?
		new = add_instruction(instr, "ra");
	else if (stack_a->size > 2 && (stack_a->array[stack_a->size - 1] < stack_a->array[1])) // rra
		new = add_instruction(instr, "rra");
	else if (need_pb(stack_a, stack_b)) // pb ?
		new = add_instruction(instr, "pb");
	else if (need_pa(stack_a, stack_b)) // pa ?
		new = add_instruction(instr, "pa");
	else if (!stack_b->size) // pb ?
	{
		new = add_instruction(instr, "pb");
		copy_a = copy_stack(stack_a);
		copy_b = copy_stack(stack_b);
		execute_instructions(new, copy_a, copy_b);
		tmp = choose_instruction(copy_a, copy_b, instr);
		if (!(ft_strcmp(tmp->line, "pa")))
		{
			remove_instruction(instr, tmp);
			remove_instruction(instr, new);
			free_stack(copy_a);
			free_stack(copy_b);
			write(STDOUT_FILENO, "pue la merde\n", 13);
			new = add_instruction(instr, "ra");
		}
		else
			remove_instruction(instr, tmp);
	}
	else
		new = add_instruction(instr, "pa");
	return (new);
}

void			resolve(t_stack *stack_a, t_stack *stack_b,
t_instruction **instr)
{
	size_t		i;
	long		pos_a;
	long		pos_b;
//	t_instruction	*ptr;
	t_instruction	*tmp;

//	ptr = NULL;
	tmp = NULL;
	i = 0;
	while ((stack_b->size || is_stack_ordered(stack_a)))
	{
		if (stack_b->size && stack_b->array[0] < stack_a->array[0])
			tmp = add_instruction(instr, "pa");
		else if (stack_a->array[0] > stack_a->array[1] && (stack_a->size < 3 || (stack_a->array[0] < stack_a->array[2])))
		{
			if (stack_b->size > 1 && stack_b->array[0] < stack_b->array[1])
				tmp = add_instruction(instr, "ss");
			else
				tmp = add_instruction(instr, "sa");
		}
		else if (stack_b->size > 1 && stack_b->array[0] < stack_b->array[1])
			tmp = add_instruction(instr, "sb");
		else if (stack_a->array[0] > stack_a->array[1] && closer_sup_pos(stack_a->array[0], stack_a) != stack_a->size)
			tmp = add_instruction(instr, "pb");
		else
		{
			pos_a = closer_sup_pos(stack_a->array[0], stack_a) - (stack_a->size / 2);
			if (stack_b->size && closer_sup_pos(stack_b->array[0], stack_b) != stack_b->size)
			{
				pos_a = closer_sup_pos(stack_b->array[0], stack_a) - (stack_a->size / 2);
				pos_b = closer_inf_pos(stack_a->array[0], stack_b) - (stack_b->size / 2);
				if ((stack_b->size < 2 || ft_abs(pos_a) <= ft_abs(pos_b)))
				{
					if (pos_a < 0 || (size_t)pos_a > stack_a->size / 2 ||
						(tmp && !ft_strcmp(tmp->line, "ra")))
						tmp = add_instruction(instr, "ra");
					else
						tmp = add_instruction(instr, "rra");
				}
				else
				{
					if (pos_b < 0 || (size_t)pos_b > stack_b->size / 2 ||
						(tmp && !ft_strcmp(tmp->line, "rb")))
						tmp = add_instruction(instr, "rb");
					else
						tmp = add_instruction(instr, "rrb");
				}
			}
			else
			{
				if (pos_a < 0 || (size_t)pos_a > stack_a->size / 2 ||
					(tmp && !ft_strcmp(tmp->line, "ra")))
					tmp = add_instruction(instr, "ra");
				else
					tmp = add_instruction(instr, "rra");
			}
		}
		execute_instructions(tmp, stack_a, stack_b);
		/*
		tmp = NULL;
		choose_instruction(stack_a, stack_b, &tmp);
		if (ptr)
			ptr->next = tmp;
		else
			*instr = tmp;
		ptr = tmp;
		execute_instructions(tmp, stack_a, stack_b);
		*/
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
