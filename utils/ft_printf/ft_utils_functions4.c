/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_functions4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:48:35 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 15:50:04 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"

void		*ft_calloc(size_t count, size_t size)
{
	void		*res;
	size_t		totalsize;

	totalsize = (count * size);
	if (!(res = malloc(totalsize)))
		return (NULL);
	ft_bzero(res, totalsize);
	return (res);
}

void		ft_bzero(void *s, size_t n)
{
	char		*res;
	size_t		i;

	if (s != NULL)
	{
		i = 0;
		res = s;
		while (n)
		{
			res[i] = 0;
			i++;
			n--;
		}
	}
}
