/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_functions3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:42:52 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 15:47:59 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

char		*ft_int_hexmax(long n, char *tab)
{
	char		*res;
	int			taille;
	int			i;

	if (n < 0)
		return (ft_int_hexmax((-n - 1), "FEDCBA9876543210"));
	else if (n > 0)
	{
		i = 0;
		taille = digit_count(n, 16);
		if (!(res = (char *)ft_calloc(1, (sizeof(char) * (taille + 1)))))
			return (NULL);
		taille--;
		while (n)
		{
			res[taille - i++] = tab[n % 16];
			n /= 16;
		}
		res[taille + 1] = '\0';
		return (res);
	}
	return (ft_strdup("0"));
}

char		*ft_int_hexmin(long n, char *tab)
{
	char		*res;
	int			taille;
	int			i;

	if (n < 0)
		return (ft_int_hexmin((-n - 1), "fedcba9876543210"));
	else if (n > 0)
	{
		i = 0;
		taille = digit_count(n, 16);
		if (!(res = (char *)ft_calloc(1, (sizeof(char) * taille + 1))))
			return (NULL);
		taille--;
		while (n)
		{
			res[taille - i++] = tab[n % 16];
			n /= 16;
		}
		res[taille + 1] = '\0';
		return (res);
	}
	return (ft_strdup("0"));
}

int			ft_uintlen(unsigned long n)
{
	int			count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void		ft_putunbr_fd(unsigned int n, int fd)
{
	if (fd < 0)
		return ;
	if (n >= 10)
	{
		ft_putunbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

size_t		digit_count(long value, int base)
{
	size_t		i;

	i = 0;
	value = (value < 0 ? -value : value);
	while (value)
	{
		value /= base;
		i++;
	}
	return (i);
}
