/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:18:20 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 18:29:03 by lpellier         ###   ########.fr       */
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

	i = -1;
	while (++i < 4)
		cub->texture[i].path = NULL;
	cub->buffer = NULL;
	cub->z_buffer = NULL;
	i = -1;
	while (++i < 4)
		cub->texture[i].img_ptr = NULL;
	cub->game.world_map = NULL;
	cub->sprite_order = NULL;
	cub->sprite_distance = NULL;
	cub->sprt = NULL;
	cub->data.img.img_ptr = NULL;
	cub->data.win_ptr = NULL;
	i = -1;
	while (++i < 3)
		cub->sprite[i].path = NULL;
	init_state2(cub);
	init_checklist(cub);
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
			return (put_error(cub, "Texture Error"));
	}
	i = -1;
	while (++i < cub->num_diff_sprites)
	{
		if (!get_sprite(cub, i))
			return (put_error(cub, "Sprite Error"));
	}
	return (1);
}
