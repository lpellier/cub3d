/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:32:57 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 15:22:35 by lpellier         ###   ########.fr       */
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
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	width = next_number(str, &index);
	str += index;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	height = next_number(str, &index);
	if (width <= 0 || height <= 0)
		return (put_error("Resolution's fucked man"));
	cub->data.img.width = width;
	cub->data.img.height = height;
	cub->nbr_elements++;
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
		return (put_error("Element unknown or map error"));
}

void		count_sprites(t_cub *cub, char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	while (*str)
	{
		if (*str == '2')
			cub->num_sprites += 1;
		str++;
	}
}

int			map_loop(t_cub *cub, char *line)
{
	int		len;

	if (line_is_map(line) && cub->nbr_elements == SUM_ELEMENTS)
	{
		cub->state.height++;
		if ((len = ft_strlen(line)) > cub->state.width)
			cub->state.width = len;
		count_sprites(cub, line);
		return (1);
	}
	else if (line_is_map(line))
		return (put_error("Map should be last element"));
	else if (check_file_element(cub, line))
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int			file_parsing(t_cub *cub, char *map_path)
{
	int			fd;
	char		*line;

	line = NULL;
	if ((fd = open(map_path, O_RDONLY)) < 0)
		return (put_error("Couldn't read map file"));
	while (get_next_line(fd, &line))
		if (!map_loop(cub, line))
			return (0);
	if (!map_loop(cub, line))
		return (0);
	close(fd);
	if (cub->nbr_elements != SUM_ELEMENTS)
		return (put_error("Hey something's wrong with your elements"));
	if (!(cub->sprites = malloc(sizeof(t_sprite) * cub->num_sprites)))
		return (0);
	if (!(cub->sprite_order = malloc(sizeof(int) * cub->num_sprites)))
		return (0);
	if (!(cub->sprite_distance = malloc(sizeof(double) * cub->num_sprites)))
		return (0);
	if (!(cub->sprt = malloc(sizeof(t_sprt) * cub->num_sprites)))
		return (0);
	if (!get_map(cub, map_path))
		return (0);
	return (1);
}
