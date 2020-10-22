/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:31:25 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/22 17:31:36 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			line_is_map(char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str >= '0' && *str <= '4')
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
			return (put_error("Map not right"));
	i = -1;
	while (++i < cub->state.height)
		if (map[i][0] != 1 || map[i][cub->state.width - 1] != 1)
			return (put_error("Map not right"));
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
		else
			free(line);
	}
	if (line_is_map(line))
		map[count_h] = strto_intp(line, count_h, cub);
	else
		free(line);
	return (map);
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
	map = second_map_loop(cub, fd, line, map);
	close(fd);
	if (!map_error(cub, map) || cub->error == 1)
		return (0);
	cub->game.world_map = map;
	return (1);
}
