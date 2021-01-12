/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:00:14 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/12 13:14:45 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_state		*add_state(t_state **states, t_state *state_from)
{
	t_state		*new;

	if (!(new = malloc(sizeof(t_state))))
		return (NULL);
}
