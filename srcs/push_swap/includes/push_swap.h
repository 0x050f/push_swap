/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 07:52:49 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/08 15:05:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# define _END		"\x1b[0m"
# define _RED		"\x1b[31m"
# define _YELLOW	"\x1b[33m"
# define _GREEN		"\x1b[32m"

# ifndef DEBUG
#	define DEBUG 0
# endif

typedef struct		s_stack
{
	int				*array;
	size_t			size;
	size_t			max_size;
}					t_stack;

typedef struct		s_instruction
{
	char			*line;
	void			*next;
	void			*prev;
}					t_instruction;

/*
** operations.c
*/

void				reverse_rotate_stack(t_stack *stack);
void				rotate_stack(t_stack *stack);
void				push_stack(t_stack *stack1, t_stack *stack2);
void				swap_stack(t_stack *stack);

/*
** stacks.c
*/

size_t				closer_inf_pos(int nb, t_stack *stack);
size_t				closer_sup_pos(int nb, t_stack *stack);
void				free_stack(t_stack *stack);
t_stack				*copy_stack(t_stack *stack);

/*
** instructions.c
*/

void				print_instructions(t_instruction *instr);
void				execute_instructions(t_instruction *instr,
t_stack *stack_a, t_stack *stack_b);
t_instruction		*add_instruction(t_instruction **instructions, char *line);
void				remove_instruction(t_instruction **instructions,
t_instruction *to_delete);

/*
** utils.c
*/

unsigned long		ft_abs(long n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *s);
void				ft_putnbr(int n);
int					ft_atoi(const char *str, int *num);

// DEBUG
void				print_stacks(t_stack *stack_a, t_stack *stack_b);

#endif
