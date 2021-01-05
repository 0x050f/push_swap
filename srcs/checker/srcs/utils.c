/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:47:45 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 01:53:54 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char		*ft_strdup(const char *str)
{
	int		i;
	char	*pt;

	i = 0;
	while (str[i])
		i++;
	if (!(pt = malloc((i + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (str[++i])
		pt[i] = str[i];
	pt[i] = '\0';
	return (pt);
}

size_t			ft_strlen(const char *s)
{
	const char *ptr;

	ptr = s;
	while (*ptr)
		++ptr;
	return (ptr - s);
}

void			ft_putnbr(int n)
{
	char c;
	long nnbr;

	nnbr = n;
	if (nnbr < 0)
	{
		write(STDOUT_FILENO, "-", 1);
		nnbr *= -1;
	}
	if (nnbr != 0)
	{
		if (nnbr / 10 > 0)
			ft_putnbr(nnbr / 10);
		c = nnbr % 10 + 48;
		write(STDOUT_FILENO, &c, 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "0", 1);
}
