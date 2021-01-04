/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:29:05 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/04 18:25:06 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

#include <stdlib.h>
#include <unistd.h>

typedef struct		s_stack
{
	int				*array;
	size_t			size;
}					t_stack;

typedef struct		s_instruction
{
	char			*line;
	void			*next;
}					t_instruction;

void			reverse_rotate_stack(t_stack *stack);
void			rotate_stack(t_stack *stack);
void			push_stack(t_stack *stack1, t_stack *stack2);
void			swap_stack(t_stack *stack);

void		execute_instructions(t_instruction *instr, t_stack *stack_a,
t_stack *stack_b);
int				add_instruction(t_instruction **intructions, char *line);
int				get_instruction(t_instruction **instructions);

/* *********************** DEBUG ******************************************** */

void			print_stacks(t_stack *stack_a, t_stack *stack_b);

#endif
