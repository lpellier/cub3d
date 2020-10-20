/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:05:42 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/09 16:10:40 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void		sprite_sorting(t_cub *cub)
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
}

void		sprite_casting4(t_cub *cub, int i)
{
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

void		sprite_casting3(t_cub *cub, int i)
{
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
			sprite_casting4(cub, i);
		}
	}
}

void		sprite_casting2(t_cub *cub, int i)
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
}
