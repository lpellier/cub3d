/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:53:25 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/05 17:15:48 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		get_pos2(char orientation, t_state *state)
{
	if (orientation == 'S')
	{
		state->dir_x = 1;
		state->dir_y = 0.001;
		state->plane_x = 0;
		state->plane_y = -0.66;
	}
	else if (orientation == 'W')
	{
		state->dir_x = 0;
		state->dir_y = -1;
		state->plane_x = -0.66;
		state->plane_y = 0;
	}
}

void		get_pos(t_cub *cub, int x, int y, char orientation)
{
	cub->state.pos_x = y + 0.5;
	cub->state.pos_y = x + 0.5;
	cub->state.valid_player = 1;
	cub->check.orientation_check++;
	if (orientation == 'N')
	{
		cub->state.dir_x = -1;
		cub->state.dir_y = 0.001;
		cub->state.plane_x = 0;
		cub->state.plane_y = 0.66;
	}
	else if (orientation == 'E')
	{
		cub->state.dir_x = 0;
		cub->state.dir_y = 1;
		cub->state.plane_x = 0.66;
		cub->state.plane_y = 0;
	}
	else
		get_pos2(orientation, &cub->state);
}

int			strto_intp2(char c, int cur, int height, t_cub *cub)
{
	int ret;

	if (c == ' ')
		ret = 1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		ret = 0;
		get_pos(cub, cur, height, c);
	}
	else if (c == '1')
		ret = 1;
	else if (c == '0')
		ret = 0;
	else if (c == '2')
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
		str[i] != 'E' && str[i] != 'W' && !(str[i] >= '0' && str[i] <= '2'))
			cub->error = 1;
	}
	while (i < cub->state.width)
	{
		map[i] = 1;
		i++;
	}
	free(str);
	return (map);
}
