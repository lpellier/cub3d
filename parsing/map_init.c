/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:55:26 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 19:23:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		get_pos2(char orientation, t_state *state)
{
	if (orientation == 35)
	{
		state->dir_x = 1;
		state->dir_y = 0;
		state->plane_x = 0;
		state->plane_y = -0.66;
	}
	else if (orientation == 39)
	{
		state->dir_x = 0;
		state->dir_y = -1;
		state->plane_x = -0.66;
		state->plane_y = 0;
	}
}

void		get_pos(int x, int y, char orientation, t_state *state)
{
	state->pos_x = y + 0.5;
	state->pos_y = x + 0.5;
	orientation -= 48;
	if (orientation == 30)
	{
		state->dir_x = -1;
		state->dir_y = 0;
		state->plane_x = 0;
		state->plane_y = 0.66;
	}
	else if (orientation == 21)
	{
		state->dir_x = 0;
		state->dir_y = 1;
		state->plane_x = 0.66;
		state->plane_y = 0;
	}
	else
		get_pos2(orientation, state);
}

int			*strto_intp(char *str, int height, t_cub *cub)
{
	int		i;
	int		count;
	int		*map;

	if (!(map = malloc(sizeof(int) * cub->state.width - 1)))
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			map[i] = 1;
		else if (str[i] == 'N' || str[i] == 'S' || \
		str[i] == 'E' || str[i] == 'W')
		{
			map[i] = 0;
			get_pos(i, height, str[i], &cub->state);
		}
		else if (str[i] == '1')
			map[i] = 1;
		else if (str[i] == '0')
			map[i] = 0;
		else if (str[i] >= '2')
		{
			map[i] = str[i] - 48;
			cub->sprites[cub->sprite_index].pos_x = height + 0.5;
			cub->sprites[cub->sprite_index].pos_y = i + 0.5;
			cub->sprites[cub->sprite_index].texture = \
			&cub->sprite[str[i] - 48 - 2];
			cub->sprite_index += 1;
		}
		else
			put_error("Map Error");
	}
	free(str);
	return (map);
}

int			line_is_map(char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str >= '0' && *str <= '9')
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

int			get_map(t_cub *cub, char *map_path)
{
	int			fd;
	int			count_h;
	int			**map;
	char		*line;

	count_h = 0;
	fd = open(map_path, O_RDONLY);
	line = NULL;
	if (!(map = malloc(sizeof(int *) * cub->state.height - 1)))
		return (0);
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
	close(fd);
	if (!map_error(cub, map))
		return (0);
	cub->game.world_map = map;
	return (1);
}
