/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:06 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/02 14:45:39 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t			count_instructions(t_instruction *instr)
{
	size_t nb;

	nb = 0;
	while (instr)
	{
		nb++;
		instr = instr->next;
	}
	return (nb);
}

int				pick_solution(t_program *prg, t_state *states)
{
	t_state			*solution;
	t_state			*tmp_state;

	solution = NULL;
	tmp_state = states->next;
	while (tmp_state)
	{
		if (!solution || count_instructions(tmp_state->instructions) <
count_instructions(solution->instructions))
			solution = tmp_state;
		tmp_state = tmp_state->next;
	}
	if (!solution)
		solution = states;
	if (solution->instructions)
	{
		execute_instructions(solution->instructions, &prg->stack_a,
&prg->stack_b, prg->debug);
		if (!(prg->instr = copy_instructions(solution->instructions)))
		{
			free_states(states);
			return (1);
		}
	}
	return (0);
}

int				realign_and_fill_a(t_program *prg)
{
	t_instruction	*tmp;

	if (prg->stack_b.size > 1 && align_stack_b(prg))
		return (1);
	while (prg->stack_b.size)
	{
		if (prg->stack_b.array[0] > prg->stack_a.array[prg->stack_a.size - 1] ||
(prg->stack_b.array[0] < prg->stack_a.array[0] &&
prg->stack_a.array[0] < prg->stack_a.array[prg->stack_a.size - 1]))
			tmp = add_instruction(&prg->instr, "pa");
		else
			tmp = add_instruction(&prg->instr, "rra");
		if (!tmp)
			return (1);
		execute_instructions(tmp, &prg->stack_a, &prg->stack_b, prg->debug);
	}
	if (align_stack_a(prg))
		return (1);
	return (0);
}

int				resolve(t_program *prg)
{
	t_state			*states;

	if (!(states = new_empty_state(&prg->stack_a, &prg->stack_b,
prg->stack_a.max_size)))
		return (1);
	if (prg->stack_a.size > 5 &&
(create_states_resolution(&states) || large_resolve(states)))
		return (1);
	if (pick_solution(prg, states))
		return (1);
	free_states(states);
	if (bruteforce_order_a(prg))
		return (1);
	if (realign_and_fill_a(prg))
		return (1);
	return (0);
}

int				main(int argc, char *argv[])
{
	t_program			prg;

	if (--argc < 1 || (!ft_strcmp(argv[1], "-v") && argc == 1))
		return (0);
	prg.debug = 0;
	if (!ft_strcmp(argv[1], "-v"))
	{
		prg.debug = 1;
		if (init_stacks(--argc, &argv[2], &prg.stack_a, &prg.stack_b))
			return (1);
	}
	else if (init_stacks(argc, &argv[1], &prg.stack_a, &prg.stack_b))
		return (1);
	if (prg.debug)
		print_stacks(&prg.stack_a, &prg.stack_b);
	prg.instr = NULL;
	if (is_stack_ordered(&prg.stack_a, ASC) && resolve(&prg))
	{
		free_instructions(prg.instr);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	print_instructions(prg.instr);
	free_prg(&prg);
	return (0);
}
