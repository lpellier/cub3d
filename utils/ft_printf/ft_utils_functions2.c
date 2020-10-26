/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:34:28 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 15:41:35 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void		ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	else if (n == -2147483648)
	{
		ft_putstr_fd("2147483648", fd);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

void		ft_putstr_fd(char *s, int fd)
{
	int i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void		ft_putnstr_fd(char *s, int size, int fd)
{
	int i;

	if (s == NULL || size == 0)
		return ;
	i = 0;
	while (s[i] && size != 0)
	{
		ft_putchar_fd(s[i], fd);
		i++;
		size--;
	}
}

int			ft_intlen(long n)
{
	int		count;

	count = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}
