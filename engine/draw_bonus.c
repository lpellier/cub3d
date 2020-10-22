/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:48:36 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/22 18:48:37 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		put_pixel(t_img *img, int x, int y, unsigned int color)
{
	img->data[y * img->width + x] = color;
}

void		draw_buffer(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->data.img.height)
	{
		j = 0;
		while (j < cub->data.img.width)
		{
			put_pixel(&cub->data.img, j, i, cub->buffer[i][j]);
			j++;
		}
		i++;
	}
}

void		put_player(t_cub *cub, int x, int y)
{
	int i;
	int j;

	i = y;
	while (i < cub->resy + y)
	{
		j = x;
		while (j < cub->resx + x)
		{
			cub->buffer[i][j] = GREEN;
			j++;
		}
		i++;
	}
}

void		put_square(t_cub *cub, int x, int y, unsigned int color)
{
	int i;
	int j;

	i = y;
	while (i < cub->resy + y)
	{
		j = x;
		while (j < cub->resx + x)
		{
			cub->buffer[i][j] = color;
			j++;
		}
		i++;
	}
}

void		draw_minimap(t_cub *cub)
{
	int		i;
	int		j;

	i = -1;
	cub->resx = cub->data.img.width / 3 / cub->state.width;
	cub->resy = cub->data.img.height / 3 / cub->state.height;
	put_player(cub, (int)((int)cub->state.pos_y * cub->resx), \
	(int)((int)cub->state.pos_x * cub->resy));
	while (++i < cub->state.width)
	{
		j = -1;
		while (++j < cub->state.height)
		{
			if (cub->game.world_map[j][i] == 1)
				put_square(cub, (int)(i * cub->resx), (int)(j * cub->resy), \
				WHITE);
			else if (cub->game.world_map[j][i] >= 2)
				put_square(cub, (int)(i * cub->resx), (int)(j * cub->resy), \
				BLUE);
		}
	}
}
