/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:55:26 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/02 16:50:05 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			line_is_map(char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str >= '0' && *str <= '2')
		return (1);
	else
		return (0);
}

int			map_error(t_cub *cub, int **map)
{
	int i;

	i = -1;
	while (++i < cub->state.width)
		if (map[0][i] != 1 || map[cub->state.height - 1][i] != 1)
			return (0);
	i = -1;
	while (++i < cub->state.height)
		if (map[i][0] != 1 || map[i][cub->state.width - 1] != 1)
			return (0);
	return (1);
}

int			**second_map_loop(t_cub *cub, int fd, char *line, int **map)
{
	int			count_h;

	count_h = 0;
	while (get_next_line(fd, &line))
	{
		if (line_is_map(line))
		{
			map[count_h] = strto_intp(line, count_h, cub);
			count_h++;
		}
		else if (!line_is_map(line) && count_h > 0 && \
		count_h <= cub->state.height - 1)
		{
			cub->error = 1;
			free(line);
		}
		else
			free(line);
	}
	if (line_is_map(line))
		map[count_h] = strto_intp(line, count_h, cub);
	else
		free(line);
	return (map);
}

int			map_is_valid(t_cub *cub, int **map)
{
	int		i;
	int		j;
	int		wall_count;

	wall_count = 0;
	i = -1;
	while (++i < cub->state.height)
	{
		j = -1;
		while (++j < cub->state.width)
		{
			if (map[i][j] == 1)
				wall_count++;
		}
	}
	if (wall_count >= 8 && cub->state.valid_player == 1)
		return (1);
	return (0);
}

int			get_map(t_cub *cub, char *map_path)
{
	int			fd;
	int			**map;
	char		*line;

	fd = open(map_path, O_RDONLY);
	line = NULL;
	if (!(map = malloc(sizeof(int *) * cub->state.height)))
		return (0);
	if (cub->state.height < 1)
		return (put_error("No map found in file"));
	map = second_map_loop(cub, fd, line, map);
	close(fd);
	if (!map_is_valid(cub, map) || !map_error(cub, map) || cub->error == 1)
		return (put_error("Map is invalid"));
	cub->game.world_map = map;
	cub->check.map_check++;
	return (1);
}
