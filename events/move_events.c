/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:22:05 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 18:24:16 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		move_forward(t_cub *cub)
{
	if (cub->state.pos_x + cub->state.dir_x * MOV >= 0)
	{
		if (cub->game.world_map[(int)(cub->state.pos_x + \
		cub->state.dir_x * MOV)][(int)cub->state.pos_y] == 0)
			cub->state.pos_x += cub->state.dir_x * MOV;
	}
	if (cub->state.pos_y + cub->state.dir_y * MOV >= 0)
	{
		if (cub->game.world_map[(int)cub->state.pos_x]\
		[(int)(cub->state.pos_y + cub->state.dir_y * MOV)] == 0)
			cub->state.pos_y += cub->state.dir_y * MOV;
	}
}

void		move_backwards(t_cub *cub)
{
	if (cub->state.pos_x - cub->state.dir_x * MOV >= 0)
	{
		if (cub->game.world_map[(int)(cub->state.pos_x - \
		cub->state.dir_x * MOV)][(int)cub->state.pos_y] == 0)
			cub->state.pos_x -= cub->state.dir_x * MOV;
	}
	if (cub->state.pos_y - cub->state.dir_y * MOV >= 0)
	{
		if (cub->game.world_map[(int)cub->state.pos_x]\
		[(int)(cub->state.pos_y - cub->state.dir_y * MOV)] == 0)
			cub->state.pos_y -= cub->state.dir_y * MOV;
	}
}

void		strafe_left(t_cub *cub)
{
	if (cub->state.pos_x - cub->state.plane_x * MOV >= 0)
	{
		if (cub->game.world_map[(int)(cub->state.pos_x - \
		cub->state.plane_x * MOV)][(int)cub->state.pos_y] == 0)
			cub->state.pos_x -= cub->state.plane_x * MOV;
	}
	if (cub->state.pos_y - cub->state.plane_y * MOV >= 0)
	{
		if (cub->game.world_map[(int)cub->state.pos_x]\
		[(int)(cub->state.pos_y - cub->state.plane_y * MOV)] == 0)
			cub->state.pos_y -= cub->state.plane_y * MOV;
	}
}

void		strafe_right(t_cub *cub)
{
	if (cub->state.pos_x + cub->state.plane_x * MOV >= 0)
	{
		if (cub->game.world_map[(int)(cub->state.pos_x + \
		cub->state.plane_x * MOV)][(int)cub->state.pos_y] == 0)
			cub->state.pos_x += cub->state.plane_x * MOV;
	}
	if (cub->state.pos_y + cub->state.plane_y * MOV >= 0)
	{
		if (cub->game.world_map[(int)cub->state.pos_x]\
		[(int)(cub->state.pos_y + cub->state.plane_y * MOV)] == 0)
			cub->state.pos_y += cub->state.plane_y * MOV;
	}
}
