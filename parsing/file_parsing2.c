/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:53:14 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 18:53:23 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			next_number(char *str, int *index)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	*index = i;
	return (res);
}

int			next_color(char *str, int *index)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i] == 32 || str[i] == 9 || str[i] == 10 \
	|| str[i] == 11 || str[i] == 12 || str[i] == 13)
		i++;
	if (str[i] == ',')
		i++;
	while (str[i] == 32 || str[i] == 9 || str[i] == 10 \
	|| str[i] == 11 || str[i] == 12 || str[i] == 13)
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	*index = i;
	return (res);
}

int			check_textures(t_cub *cub, char *str)
{
	int index;

	index = 0;
	if (*str == 'N')
		index = 1;
	else if (*str == 'E')
		index = 2;
	else if (*str == 'W')
		index = 3;
	str += 2;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (!(cub->texture[index].path = ft_strdup(str)))
		return (0);
	return (1);
}

int			check_sprite(t_cub *cub, char *str)
{
	int index;

	str += 1;
	index = 0;
	if (*str == '2')
		index = 1;
	else if (*str == '3')
		index = 2;
	str += 1;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (!(cub->sprite[index].path = ft_strdup(str)))
		return (0);
	return (1);
}

int			check_colors(t_cub *cub, char *str)
{
	int r;
	int g;
	int b;
	int index;
	int *rgb;

	if (*str == 'F')
		rgb = &cub->floor_color;
	else if (*str == 'C')
		rgb = &cub->ceil_color;
	str++;
	r = next_color(str, &index);
	str += index;
	g = next_color(str, &index);
	str += index;
	b = next_color(str, &index);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (put_error("Color Error - Please choose \
		three integers between 0 and 255"));
	*rgb = 65536 * r + 256 * g + b;
	if (*rgb >= 0 && *rgb <= 2147483647)
		return (1);
	return (0);
}
