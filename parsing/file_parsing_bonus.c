/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:29:00 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 16:05:06 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			check_resolution(t_cub *cub, char *str)
{
	int width;
	int height;
	int index;

	index = 0;
	str++;
	if (*str != 32 && *str != 9 && *str != 10 \
	&& *str != 11 && *str != 12 && *str != 13)
		return (put_error(cub, "Resolution's fucked man"));
	width = next_number(str, &index);
	str += index;
	height = next_number(str, &index);
	str += index;
	if (width <= 0 || height <= 0 || next_number(str, &index) > 0)
		return (put_error(cub, "Resolution's fucked man"));
	cub->data.img.width = width;
	cub->data.img.height = height;
	cub->check.res_check += 1;
	return (1);
}

int			check_file_element(t_cub *cub, char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == 'R')
		return (check_resolution(cub, str));
	else if ((*str == 'N' && *(str + 1) == 'O') || (*(str) == 'S' && \
	*(str + 1) == 'O') || (*str == 'E' && *(str + 1) == 'A') || \
	(*(str) == 'W' && *(str + 1) == 'E'))
		return (check_textures(cub, str));
	else if (*str == 'S')
		return (check_sprite(cub, str));
	else if (*str == 'F' || *str == 'C')
		return (check_colors(cub, str));
	else if (*str == '1' || !*str)
		return (1);
	else
		return (0);
}

void		count_sprites(t_cub *cub, char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	while (*str)
	{
		if (*str == '2' || *str == '3' || *str == '4')
			cub->num_sprites += 1;
		str++;
	}
}

int			map_is_last(t_cub *cub)
{
	if (cub->check.res_check == 1 && cub->check.c_ceil_check == 1\
	&& cub->check.c_floor_check == 1 && cub->check.ea_text_check == 1 \
	&& cub->check.no_text_check == 1 && cub->check.sprt_check == 3 \
	&& cub->check.we_text_check == 1 && cub->check.so_text_check == 1)
		return (1);
	return (0);
}

int			file_parsing(t_cub *cub, char *map_path)
{
	int			fd;
	char		*line;

	line = NULL;
	if ((fd = open(map_path, O_RDONLY)) < 0)
		return (put_error(cub, "Couldn't read map file"));
	while (get_next_line(fd, &line))
		if (!map_loop(cub, line))
			return (0);
	if (!map_loop(cub, line))
		return (0);
	close(fd);
	if (!(cub->sprites = malloc(sizeof(t_sprite) * cub->num_sprites)))
		return (0);
	if (!(cub->sprite_order = malloc(sizeof(int) * cub->num_sprites)))
		return (0);
	if (!(cub->sprite_distance = malloc(sizeof(double) * cub->num_sprites)))
		return (0);
	if (!(cub->sprt = malloc(sizeof(t_sprt) * cub->num_sprites)))
		return (0);
	if (!get_map(cub, map_path) || !check_elements(cub))
		return (0);
	return (1);
}
