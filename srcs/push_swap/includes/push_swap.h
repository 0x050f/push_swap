/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 07:52:49 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 09:08:37 by lmartin          ###   ########.fr       */
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

typedef struct		s_stack
{
	int				*array;
	size_t			size;
}					t_stack;

/*
** operations.c
*/

void			reverse_rotate_stack(t_stack *stack);
void			rotate_stack(t_stack *stack);
void			push_stack(t_stack *stack1, t_stack *stack2);
void			swap_stack(t_stack *stack);

/*
** utils.c
*/

size_t		ft_strlen(const char *s);
void		ft_putnbr(int n);
int			ft_atoi(const char *str, int *num);

// DEBUG
void			print_stacks(t_stack *stack_a, t_stack *stack_b);

#endif
