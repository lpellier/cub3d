/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:29:00 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/02 15:15:41 by lpellier         ###   ########.fr       */
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
	width = next_number(str, &index);
	str += index;
	height = next_number(str, &index);
	str += index;
	if (width <= 0 || height <= 0 || next_number(str, &index) > 0)
		return (put_error("Resolution's fucked man"));
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
		return (put_error("Element unknown or map error"));
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
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

void	print_map(t_cub *cub)
{
	int		i;
	int		j;
	
	i = -1;
	while (++i < cub->state.height)
	{
		j = -1;
		while (++j < cub->state.width)
		{
			if (i == (int)cub->state.pos_x && j == (int)cub->state.pos_y)
				ft_printf("\033[42m  \033[0m");
			else if (cub->game.world_map[i][j] >= 2 && cub->game.world_map[i][j] <= 4)
				ft_printf("\033[44m  \033[0m", cub->game.world_map[i][j]);
			else if (cub->game.world_map[i][j] == 1)
				ft_printf("\033[40m  \033[0m", cub->game.world_map[i][j]);
			else
				ft_printf("\033[49m  \033[0m", cub->game.world_map[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\033[0m");
}

int			check_elements(t_cub *cub)
{
	if (cub->check.res_check != 1)
		return (put_error("Only one resolution permitted in map file."));
	else if (cub->check.c_ceil_check != 1)
		return (put_error("Only one ceiling color permitted in map file."));
	else if (cub->check.c_floor_check != 1)
		return (put_error("Only one floor color permitted in map file."));
	else if (cub->check.no_text_check != 1)
		return (put_error("Only one NO texture permitted in map file."));
	else if (cub->check.so_text_check != 1)
		return (put_error("Only one SO texture permitted in map file."));
	else if (cub->check.ea_text_check != 1)
		return (put_error("Only one EA texture permitted in map file."));
	else if (cub->check.we_text_check != 1)
		return (put_error("Only one WE texture permitted in map file."));
	else if (cub->check.sprt_check != cub->num_diff_sprites)
		return (put_error("Wrong number of sprites (usually one, \
two or three for bonus) in map file."));
	else if (cub->check.orientation_check != 1)
		return (put_error("Only one player permitted in map."));
	else if (cub->check.map_check != 1)
		return (put_error("Only one map permitted in map file."));
	ft_printf("RES     [OK]\nCEIL    [OK]\nFLOOR   [OK]\nNO      [OK]\nEA      [OK]\nSO      [OK]\
	\nWE      [OK]\nPLAYER  [OK]\nMAP     [OK]\n\n");
	print_map(cub);
	return (1);
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
