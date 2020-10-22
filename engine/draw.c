/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:06:32 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/22 18:49:19 by lpellier         ###   ########.fr       */
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
