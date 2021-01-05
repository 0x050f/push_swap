/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:29:05 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 01:50:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

#include <stdlib.h>
#include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

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

/* operations.c */
void			reverse_rotate_stack(t_stack *stack);
void			rotate_stack(t_stack *stack);
void			push_stack(t_stack *stack1, t_stack *stack2);
void			swap_stack(t_stack *stack);

/* instructions.c */
void			execute_instructions(t_instruction *instr, t_stack *stack_a,
t_stack *stack_b);
int				add_instruction(t_instruction **intructions, char *line);
int				get_instruction(t_instruction **instructions);

/* utils.c */
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
size_t			ft_strlen(const char *s);
void			ft_putnbr(int n);

/* debug.c */
void			print_stacks(t_stack *stack_a, t_stack *stack_b);
void			print_instructions(t_instruction *instructions);

#endif
