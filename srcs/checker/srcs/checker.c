/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:28:53 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/03 10:03:42 by marvin           ###   ########.fr       */
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
** Read and fill intructions chained list
*/

int				init_instructions(t_program *prg)
{
	int			ret;
	char		buff[1];

	prg->instr = NULL;
	ret = get_instruction(&prg->instr);
	while (ret > 0)
		ret = get_instruction(&prg->instr);
	if (ret < 0)
	{
		buff[0] = ' ';
		while (buff[0] && read(STDIN_FILENO, &buff, 1))
			;
		free_instructions(prg->instr);
		free(prg->stack_a.array);
		free(prg->stack_b.array);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	t_program		prg;

	if (--argc < 1 || (!ft_strcmp(argv[1], "-v") && argc == 1))
		return (0);
	prg.debug = 0;
	if (!ft_strcmp(argv[1], "-v"))
	{
		if ((prg.debug = 1) &&
init_stacks(--argc, &argv[2], &prg.stack_a, &prg.stack_b))
			return (1);
	}
	else if (init_stacks(argc, &argv[1], &prg.stack_a, &prg.stack_b))
		return (1);
	if (init_instructions(&prg))
		return (1);
	if (prg.debug)
		print_instructions(prg.instr);
	if (prg.debug)
		print_stacks(&prg.stack_a, &prg.stack_b);
	execute_instructions(prg.instr, &prg.stack_a, &prg.stack_b, prg.debug);
	if (is_stack_ordered(&prg.stack_a) || prg.stack_b.size)
		write(STDOUT_FILENO, "KO\n", 3);
	else
		write(STDOUT_FILENO, "OK\n", 3);
	return (free_prg(&prg));
}
