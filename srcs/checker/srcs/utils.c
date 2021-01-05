/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:47:45 by lmartin           #+#    #+#             */
/*   Updated: 2021/01/05 03:02:33 by lmartin          ###   ########.fr       */
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

size_t		ft_strlen(const char *s)
{
	const char *ptr;

	ptr = s;
	while (*ptr)
		++ptr;
	return (ptr - s);
}

void		ft_putnbr(int n)
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

/*
** atoi passing a pointer to the number in parameter and returning 1 if there is
** an error (not a number or not a integer)
*/

int			ft_atoi(const char *str, int *num)
{
	char	*ptr;
	long	nbr;
	int		sign;
	size_t	i;

	ptr = (char *)str;
	nbr = 0;
	sign = 1;
	if (*ptr == '-' && ptr++)
		sign *= -1;
	i = 0;
	while (*ptr >= '0' && *ptr <= '9' && i++ < 9)
		nbr = nbr * 10 + *ptr++ - '0';
	if (*ptr != '\0' || nbr > 2147483647 || nbr < -2147483648)
		return (1);
	*num = nbr * sign;
	return (0);
}
