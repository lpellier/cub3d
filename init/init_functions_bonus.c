/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:18:20 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/26 19:20:22 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			init_buffer(t_cub *cub)
{
	int		i;

	if (!(cub->buffer = malloc(sizeof(int *) * cub->data.img.height)))
		return (0);
	i = -1;
	while (++i < cub->data.img.height)
		if (!(cub->buffer[i] = malloc(sizeof(int) * cub->data.img.width)))
			return (0);
	if (!(cub->z_buffer = malloc(sizeof(double) * cub->data.img.width)))
		return (0);
	return (1);
}

void		init_state(t_cub *cub)
{
	int		i;

	cub->state.time = (double)clock();
	cub->state.valid_player = 0;
	cub->nbr_elements = 0;
	cub->error = 0;
	cub->resx = 0;
	cub->resy = 0;
	cub->state.old_time = 0;
	cub->state.width = 0;
	cub->state.height = 0;
	cub->num_sprites = 0;
	cub->sprite_index = 0;
	cub->num_diff_sprites = 0;
	cub->ray.draw_start = 0;
	i = -1;
	while (++i < 66000)
		cub->game.keys[i] = 0;
}

int			get_texture(t_cub *cub, int index)
{
	t_img *a;

	a = &cub->texture[index];
	if (!(a->img_ptr = mlx_xpm_file_to_image(cub->data.mlx_ptr, a->path, \
	&a->width, &a->height)))
		return (0);
	a->data = (unsigned int *)mlx_get_data_addr(a->img_ptr, &a->bpp, \
	&a->size_l, &a->endian);
	return (1);
}

int			get_sprite(t_cub *cub, int index)
{
	t_img *a;

	a = &cub->sprite[index];
	if (!(a->img_ptr = mlx_xpm_file_to_image(cub->data.mlx_ptr, a->path, \
	&a->width, &a->height)))
		return (0);
	a->data = (unsigned int *)mlx_get_data_addr(a->img_ptr, &a->bpp, \
	&a->size_l, &a->endian);
	return (1);
}

int			get_tex_sprite(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (!get_texture(cub, i))
			return (put_error("Texture Error"));
	}
	i = -1;
	while (++i < cub->num_diff_sprites)
	{
		if (!get_sprite(cub, i))
			return (put_error("Sprite Error"));
	}
	return (1);
}