/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:27:53 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 18:28:11 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	i = 0;
	if (s1 != NULL)
	{
		if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
			return (NULL);
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		if (start >= (unsigned int)ft_strlen(s) || !(*s) || len == 0)
			return (ft_strdup("\0"));
		if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (s[start + i] && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (ft_strdup("\0"));
}

int		check_n(char *stock)
{
	int		i;

	i = 0;
	if (stock == NULL)
		return (0);
	while (*stock)
	{
		if (*stock == '\n')
			return (i + 1);
		stock++;
		i++;
	}
	return (0);
}
