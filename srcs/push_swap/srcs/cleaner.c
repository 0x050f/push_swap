/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:14:58 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/23 15:17:41 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			free_instructions(t_instruction *instructions)
{
	t_instruction	*next;

	while (instructions)
	{
		next = instructions->next;
		free(instructions->line);
		free(instructions);
		instructions = next;
	}
}

void			free_stack(t_stack *stack)
{
	free(stack->array);
	free(stack);
}
