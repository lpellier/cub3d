/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 21:09:25 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/08 19:17:59 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			cmp(const void *left, const void *right)
{
	t_sprt *a;
	t_sprt *b;

	a = (t_sprt *)left;
	b = (t_sprt *)right;
	if (b->dist < a->dist)
		return (1);
	else if (a->dist < b->dist)
		return (-1);
	else
		return ((a->order < b->order) - (b->order < a->order));
}

void		sort_sprites(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->num_sprites)
	{
		cub->sprt[i].dist = cub->sprite_distance[i];
		cub->sprt[i].order = cub->sprite_order[i];
	}
	qsort(cub->sprt, cub->num_sprites, sizeof(t_sprt), cmp);
	i = -1;
	while (++i < cub->num_sprites)
	{
		cub->sprite_distance[i] = cub->sprt[cub->num_sprites - i - 1].dist;
		cub->sprite_order[i] = cub->sprt[cub->num_sprites - i - 1].order;
	}
}

void		sprite_casting(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->num_sprites)
	{
		cub->sprite_order[i] = i;
		cub->sprite_distance[i] = ((cub->state.pos_x - cub->sprites[i].pos_x)\
		* (cub->state.pos_x - cub->sprites[i].pos_x) + (cub->state.pos_y - \
		cub->sprites[i].pos_y) * (cub->state.pos_y - cub->sprites[i].pos_y));
	}
	sort_sprites(cub);
	i = -1;
	while (++i < cub->num_sprites)
	{
		cub->ray.sprite_x = cub->sprites[cub->sprite_order[i]].pos_x - \
		cub->state.pos_x;
		cub->ray.sprite_y = cub->sprites[cub->sprite_order[i]].pos_y - \
		cub->state.pos_y;
		cub->ray.inv_det = 1.0 / (cub->state.plane_x * cub->state.dir_y - \
		cub->state.dir_x * cub->state.plane_y);
		cub->ray.transform_x = cub->ray.inv_det * (cub->state.dir_y * \
		cub->ray.sprite_x - cub->state.dir_x * cub->ray.sprite_y);
		cub->ray.transform_y = cub->ray.inv_det * (-cub->state.plane_y * \
		cub->ray.sprite_x + cub->state.plane_x * cub->ray.sprite_y);
		cub->ray.sprite_screen_x = (int)((cub->data.img.width / 2) * \
		(1 + cub->ray.transform_x / cub->ray.transform_y));
		cub->ray.sprite_height = abs((int)(cub->data.img.height / \
		(cub->ray.transform_y)));
		cub->ray.draw_start_y = -cub->ray.sprite_height / 2 + \
		cub->data.img.height / 2;
		if (cub->ray.draw_start_y < 0)
			cub->ray.draw_start_y = 0;
		cub->ray.draw_end_y = cub->ray.sprite_height / 2 + \
		cub->data.img.height / 2;
		if (cub->ray.draw_end_y >= cub->data.img.height)
			cub->ray.draw_end_y = cub->data.img.height - 1;
		cub->ray.sprite_width = abs((int)(cub->data.img.height / \
		(cub->ray.transform_y)));
		cub->ray.draw_start_x = -cub->ray.sprite_width / 2 + \
		cub->ray.sprite_screen_x;
		if (cub->ray.draw_start_x < 0)
			cub->ray.draw_start_x = 0;
		cub->ray.draw_end_x = cub->ray.sprite_width / 2 + \
		cub->ray.sprite_screen_x;
		if (cub->ray.draw_end_x >= cub->data.img.width)
			cub->ray.draw_end_x = cub->data.img.width - 1;
		cub->ray.stripe = cub->ray.draw_start_x - 1;
		while (++cub->ray.stripe < cub->ray.draw_end_x)
		{
			cub->ray.tex_sprite_x = (int)(256 * (cub->ray.stripe - \
			(-cub->ray.sprite_width / 2 + cub->ray.sprite_screen_x)) * \
			cub->sprites[cub->sprite_order[i]].texture->width / \
			cub->ray.sprite_width) / 256;
			if (cub->ray.transform_y > 0 && cub->ray.stripe > 0 && \
			cub->ray.stripe < cub->data.img.width && cub->ray.transform_y < \
			cub->z_buffer[cub->ray.stripe])
			{
				cub->ray.y = cub->ray.draw_start_y - 1;
				while (++cub->ray.y < cub->ray.draw_end_y)
				{
					cub->ray.d = (cub->ray.y) * 256 - cub->data.img.height * \
					128 + cub->ray.sprite_height * 128;
					cub->ray.tex_sprite_y = ((cub->ray.d * \
					cub->sprites[cub->sprite_order[i]].texture->height) / \
					cub->ray.sprite_height) / 256;
					cub->ray.color = cub->sprites[cub->sprite_order[i]].\
					texture->data[cub->sprites[cub->sprite_order[i]].texture\
					->width * cub->ray.tex_sprite_y + cub->ray.tex_sprite_x];
					if ((cub->ray.color & 0x00FFFFFF) != 0)
						cub->buffer[cub->ray.y][cub->ray.stripe] = \
						cub->ray.color;
				}
			}
		}
	}
}

void		raycasting(t_cub *cub)
{
	int x;

	x = -1;
	while (++x < cub->data.img.width)
	{
		cub->ray.camera_x = 2 * x / (double)cub->data.img.width - 1;
		cub->ray.raydir_x = cub->state.dir_x + cub->state.plane_x * \
		cub->ray.camera_x;
		cub->ray.raydir_y = cub->state.dir_y + cub->state.plane_y * \
		cub->ray.camera_x;
		cub->ray.map_x = (int)cub->state.pos_x;
		cub->ray.map_y = (int)cub->state.pos_y;
		if (cub->ray.raydir_y == 0)
			cub->ray.delta_dist_x = 0;
		else if (cub->ray.raydir_x == 0)
			cub->ray.delta_dist_x = 1;
		else
			cub->ray.delta_dist_x = fabs(1 / cub->ray.raydir_x);
		if (cub->ray.raydir_x == 0)
			cub->ray.delta_dist_y = 0;
		else if (cub->ray.raydir_y == 0)
			cub->ray.delta_dist_y = 0;
		else
			cub->ray.delta_dist_y = fabs(1 / cub->ray.raydir_y);
		cub->ray.hit = 0;
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
		cub->ray.line_height = (int)(cub->data.img.height / \
		cub->ray.perp_wall_dist);
		cub->ray.draw_start = -cub->ray.line_height / 2 + \
		cub->data.img.height / 2;
		if (cub->ray.draw_start < 0)
			cub->ray.draw_start = 0;
		cub->ray.draw_end = cub->ray.line_height / 2 + cub->data.img.height / 2;
		if (cub->ray.draw_end >= cub->data.img.height)
			cub->ray.draw_end = cub->data.img.height - 1;
		if (cub->ray.side == 0)
			cub->ray.wall_x = cub->state.pos_y + cub->ray.perp_wall_dist * \
			cub->ray.raydir_y;
		else
			cub->ray.wall_x = cub->state.pos_x + cub->ray.perp_wall_dist * \
			cub->ray.raydir_x;
		cub->ray.wall_x -= floor((cub->ray.wall_x));
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
		cub->ray.tex_pos = (cub->ray.draw_start - cub->data.img.height / \
		2 + cub->ray.line_height / 2) * cub->ray.step;
		cub->ray.j = -1;
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
		cub->z_buffer[x] = cub->ray.perp_wall_dist;
	}
	sprite_casting(cub);
	draw_minimap(cub);
	draw_buffer(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, \
	cub->data.img.img_ptr, 0, 0);
}
