/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:50:51 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 16:08:41 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				map_loop(t_cub *cub, char *line)
{
	int		len;

	if (line_is_map(line) && map_is_last(cub))
	{
		cub->state.height++;
		if ((len = ft_strlen(line)) > cub->state.width)
			cub->state.width = len;
		count_sprites(cub, line);
	}
	else if (line_is_map(line))
		return (put_error(cub, "Map should be last element of map file."));
	else if (check_file_element(cub, line) == -1)
	{
		free(line);
		return (put_error(cub, "Element unknown or map error."));
	}
	if (cub->error == 1)
		return (0);
	free(line);
	return (1);
}

void			print_map(t_cub *cub)
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
			else if (cub->game.world_map[i][j] >= 2 && \
			cub->game.world_map[i][j] <= 4)
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

int				check_elements(t_cub *cub)
{
	if (cub->check.res_check != 1)
		return (put_error(cub, "Gotta have one resolution  in map file."));
	else if (cub->check.c_ceil_check != 1)
		return (put_error(cub, "Gotta have one ceiling color in map file."));
	else if (cub->check.c_floor_check != 1)
		return (put_error(cub, "Gotta have one floor color in map file."));
	else if (cub->check.no_text_check != 1)
		return (put_error(cub, "Gotta have one NO texture in map file."));
	else if (cub->check.so_text_check != 1)
		return (put_error(cub, "Gotta have one SO texture in map file."));
	else if (cub->check.ea_text_check != 1)
		return (put_error(cub, "Gotta have one EA texture in map file."));
	else if (cub->check.we_text_check != 1)
		return (put_error(cub, "Gotta have one WE texture in map file."));
	else if (cub->check.sprt_check != cub->num_diff_sprites)
		return (put_error(cub, "Wrong number of sprites (usually one, \
		two or three for bonus) in map file."));
	else if (cub->check.orientation_check != 1)
		return (put_error(cub, "Gotta have one player in map."));
	else if (cub->check.map_check != 1)
		return (put_error(cub, "Gotta have one map in map file."));
	print_map(cub);
	return (1);
}

void			init_checklist(t_cub *cub)
{
	cub->check.res_check = 0;
	cub->check.c_floor_check = 0;
	cub->check.c_ceil_check = 0;
	cub->check.no_text_check = 0;
	cub->check.so_text_check = 0;
	cub->check.ea_text_check = 0;
	cub->check.we_text_check = 0;
	cub->check.sprt_check = 0;
	cub->check.orientation_check = 0;
	cub->check.map_check = 0;
}

int				check_colors2(t_cub *cub, char *str)
{
	while (*str)
	{
		if (!white_space(*str) && *str != '\0')
			return (put_error(cub, "Color error my dude"));
		str++;
	}
	return (1);
}
