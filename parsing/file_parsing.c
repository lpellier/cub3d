/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:32:57 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 19:09:31 by lpellier         ###   ########.fr       */
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
	cub->data.img.width = width;
	cub->data.img.height = height;
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

int			map_loop(t_cub *cub, char *line)
{
	int		len;

	if (line_is_map(line))
	{
		cub->state.height++;
		if ((len = ft_strlen(line)) > cub->state.width)
			cub->state.width = len;
		count_sprites(cub, line);
	}
	else if (!check_file_element(cub, line))
		return (put_error("Element unknown or map error"));
	free(line);
	return (1);
}

int			file_parsing(t_cub *cub, char *map_path)
{
	int			fd;
	char		*line;

	line = NULL;
	if (!(fd = open(map_path, O_RDONLY)))
		exit(0);
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
	if (!get_map(cub, map_path))
		return (0);
	return (1);
}
