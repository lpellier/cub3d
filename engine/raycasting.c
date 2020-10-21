/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 21:09:25 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/21 18:34:34 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void		sprite_casting(t_cub *cub)
{
	int i;

	i = -1;
	sprite_sorting(cub);
	while (++i < cub->num_sprites)
	{
		sprite_casting2(cub, i);
		cub->ray.draw_start_x = -cub->ray.sprite_width / 2 + \
		cub->ray.sprite_screen_x;
		if (cub->ray.draw_start_x < 0)
			cub->ray.draw_start_x = 0;
		cub->ray.draw_end_x = cub->ray.sprite_width / 2 + \
		cub->ray.sprite_screen_x;
		if (cub->ray.draw_end_x >= cub->data.img.width)
			cub->ray.draw_end_x = cub->data.img.width - 1;
		cub->ray.stripe = cub->ray.draw_start_x - 1;
		sprite_casting3(cub, i);
	}
}

void		raycasting2(t_cub *cub, int x)
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
}

void		raycasting(t_cub *cub)
{
	int x;

	x = -1;
	while (++x < cub->data.img.width)
	{
		raycasting2(cub, x);
		raycasting3(cub);
		raycasting4(cub);
		raycasting5(cub);
		raycasting6(cub);
		raycasting7(cub, x);
		cub->z_buffer[x] = cub->ray.perp_wall_dist;
	}
	sprite_casting(cub);
	draw_minimap(cub);
	draw_buffer(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, \
	cub->data.img.img_ptr, 0, 0);
}
