/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:03:21 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/27 14:37:04 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		raycasting7(t_cub *cub, int x)
{
	while (++cub->ray.j < cub->ray.draw_start)
	{
		cub->ray.color = cub->ceil_color;
		cub->buffer[cub->ray.j][x] = cub->ray.color;
	}
	cub->ray.j = cub->ray.draw_start - 1;
	while (++cub->ray.j < cub->ray.draw_end)
	{
		cub->ray.tex_y = (int)cub->ray.tex_pos & (cub->texture\
		[cub->ray.tex_num].height - 1);
		cub->ray.tex_pos += cub->ray.step;
		cub->ray.color = cub->texture[cub->ray.tex_num].data[cub->texture\
		[cub->ray.tex_num].height * cub->ray.tex_y + cub->ray.tex_x];
		if (cub->ray.side == 1)
			cub->ray.color = (cub->ray.color >> 1) & 8355711;
		if (cub->ray.perp_wall_dist > 5)
			cub->ray.color = (cub->ray.color >> 1) & 8355711;
		cub->buffer[cub->ray.j][x] = cub->ray.color;
	}
	cub->ray.j = cub->ray.draw_end - 1;
	while (++cub->ray.j < cub->data.img.height)
	{
		cub->ray.color = cub->floor_color;
		cub->buffer[cub->ray.j][x] = cub->ray.color;
	}
}

void		raycasting6(t_cub *cub)
{
	if (cub->ray.draw_end >= cub->data.img.height)
		cub->ray.draw_end = cub->data.img.height - 1;
	if (cub->ray.side == 0)
		cub->ray.wall_x = cub->state.pos_y + cub->ray.perp_wall_dist * \
		cub->ray.raydir_y;
	else
		cub->ray.wall_x = cub->state.pos_x + cub->ray.perp_wall_dist * \
		cub->ray.raydir_x;
	cub->ray.wall_x -= (int)(cub->ray.wall_x);
	cub->ray.tex_x = (int)(cub->ray.wall_x * (double)\
	(cub->texture[cub->ray.tex_num].width));
	if (cub->ray.side == 0 && cub->ray.raydir_x > 0)
		cub->ray.tex_x = cub->texture[cub->ray.tex_num].width - \
		cub->ray.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.raydir_y < 0)
		cub->ray.tex_x = cub->texture[cub->ray.tex_num].width - \
		cub->ray.tex_x - 1;
	cub->ray.step = 1.0 * cub->texture[cub->ray.tex_num].height / \
	cub->ray.line_height;
	if (cub->ray.draw_end == cub->ray.draw_start)
		printf("%f\n", cub->ray.perp_wall_dist);
	cub->ray.tex_pos = (cub->ray.draw_start - cub->data.img.height / \
	2 + cub->ray.line_height / 2) * cub->ray.step;
	cub->ray.j = -1;
}

void		raycasting5(t_cub *cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.perp_wall_dist = (cub->ray.map_x - cub->state.pos_x + \
		(1 - cub->ray.step_x) / 2) / cub->ray.raydir_x;
		if (cub->ray.raydir_x > 0)
			cub->ray.tex_num = 0;
		else
			cub->ray.tex_num = 1;
	}
	else
	{
		cub->ray.perp_wall_dist = (cub->ray.map_y - cub->state.pos_y + \
		(1 - cub->ray.step_y) / 2) / cub->ray.raydir_y;
		if (cub->ray.raydir_y > 0)
			cub->ray.tex_num = 2;
		else
			cub->ray.tex_num = 3;
	}
	cub->ray.perp_wall_dist = cub->ray.perp_wall_dist < 0.001 ? 0.001 : cub->ray.perp_wall_dist;
	cub->ray.line_height = (int)(cub->data.img.height / \
	cub->ray.perp_wall_dist);
	cub->ray.draw_start = -cub->ray.line_height / 2 + \
	cub->data.img.height / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + cub->data.img.height / 2;
}

void		raycasting4(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->game.world_map[cub->ray.map_x][cub->ray.map_y] == 1)
			cub->ray.hit = 1;
	}
}

void		raycasting3(t_cub *cub)
{
	if (cub->ray.raydir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->state.pos_x - cub->ray.map_x) * \
		cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->state.pos_x) * \
		cub->ray.delta_dist_x;
	}
	if (cub->ray.raydir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->state.pos_y - cub->ray.map_y) * \
		cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->state.pos_y) * \
		cub->ray.delta_dist_y;
	}
}
