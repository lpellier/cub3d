/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:33:01 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 14:49:27 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	state->valid_player = 1;
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

int			strto_intp2(char c, int cur, int height, t_cub *cub)
{
	int ret;

	if (c == ' ')
		ret = 1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		ret = 0;
		get_pos(cur, height, c, &cub->state);
	}
	else if (c == '1')
		ret = 1;
	else if (c == '0')
		ret = 0;
	else if (c >= '2' && c <= '4')
	{
		ret = c - 48;
		cub->sprites[cub->sprite_index].pos_x = height + 0.5;
		cub->sprites[cub->sprite_index].pos_y = cur + 0.5;
		cub->sprites[cub->sprite_index].texture = \
		&cub->sprite[c - 48 - 2];
		cub->sprite_index += 1;
	}
	else
		ret = -1;
	return (ret);
}

int			*strto_intp(char *str, int height, t_cub *cub)
{
	int		i;
	int		*map;

	if (!(map = malloc(sizeof(int) * cub->state.width)))
		return (NULL);
	i = -1;
	while (str[++i])
	{
		map[i] = strto_intp2(str[i], i, height, cub);
		if (str[i] != ' ' && str[i] != 'N' && str[i] != 'S' && \
		str[i] != 'E' && str[i] != 'W' && !(str[i] >= '0' && str[i] <= '4'))
		{
			put_error("Map Error");
			cub->error = 1;
		}
	}
	while (i < cub->state.width)
	{
		map[i] = 1;
		i++;
	}
	free(str);
	return (map);
}
