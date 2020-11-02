/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:21:15 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/02 17:05:51 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			next_number(char *str, int *index)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (white_space(str[i]))
		i++;
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
	while (white_space(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	while (white_space(str[i]))
		i++;
	if (str[i] == '-' || !(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != '\0' && str[i] != 32 && str[i] != 9 && str[i] != 10 \
	&& str[i] != 11 && str[i] != 12 && str[i] != 13 && str[i] != ',')
		return (-1);
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
	if (!white_space(*str))
		return (put_error("Your texture's all fucked up"));
	while (white_space(*str))
		str++;
	if (!(cub->texture[index].path = ft_strdup(str)))
		return (put_error("Your texture's all fucked up"));
	if (index == 0)
		cub->check.so_text_check += 1;
	else if (index == 1)
		cub->check.no_text_check += 1;
	else if (index == 2)
		cub->check.ea_text_check += 1;
	else if (index == 3)
		cub->check.we_text_check += 1;
	return (1);
}

int			check_sprite(t_cub *cub, char *str)
{
	int index;

	str += 1;
	cub->num_diff_sprites++;
	if (*str == '1')
		index = 0;
	else if (*str == '2')
		index = 1;
	else if (*str == '3')
		index = 2;
	else
		return (put_error("Your sprite's all fucked up"));
	str += 1;
	if (*str != 32 && *str != 9 && *str != 10 \
	&& *str != 11 && *str != 12 && *str != 13)
		return (put_error("Your sprite's all fucked up"));
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (!(cub->sprite[index].path = ft_strdup(str)))
		return (put_error("Your sprite's all fucked up"));
	cub->check.sprt_check++;
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
	cub->check.c_floor_check += *str == 'F' ? 1 : 0;
	cub->check.c_ceil_check += *str == 'C' ? 1 : 0;
	str++;
	if (!white_space(*str))
		return (put_error("Color error my dude"));
	if ((r = next_color(str, &index)) == -1)
		return (put_error("Color error my dude"));
	str += index;
	if ((g = next_color(str, &index)) == -1)
		return (put_error("Color error my dude"));
	str += index;
	if ((b = next_color(str, &index)) == -1)
		return (put_error("Color error my dude"));
	str += index;
	*rgb = 65536 * r + 256 * g + b;
	if (r > 255 || g > 255 || b > 255 \
	|| !(*rgb >= 0 && *rgb <= 2147483647) || next_color(str, &index) > 0)
		return (put_error("Color error my dude"));
	while (*str)
	{
		if (!white_space(*str) && *str != '\0')
			return (put_error("Color error my dude"));
		str++;
	}
	return (1);
}
