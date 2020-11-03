/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:02:34 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 18:10:51 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		free_buffer(t_cub *cub)
{
	int i;

	i = -1;
	
	if (cub->buffer != NULL)
	{
		while (++i < cub->data.img.height)
		{
			if (cub->buffer[i] != NULL)
				free(cub->buffer[i]);
			cub->buffer[i] = NULL;
		}
	free(cub->buffer);
	}
	cub->buffer = NULL;
	if (cub->z_buffer != NULL)
		free(cub->z_buffer);
	cub->z_buffer = NULL;
	if (cub->sprites != NULL)
		free(cub->sprites);
	cub->sprites = NULL;
}

void		free_and_destroy2(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub->texture[i].img_ptr != NULL)
			mlx_destroy_image(cub->data.mlx_ptr, cub->texture[i].img_ptr);
		cub->texture[i].img_ptr = NULL;
	}
	i = -1;
	while (++i < cub->num_diff_sprites)
	{
		if (cub->sprite[i].path != NULL)
			free(cub->sprite[i].path);
		cub->sprite[i].path = NULL;
	}
	if (cub->sprite_order != NULL)
		free(cub->sprite_order);
	cub->sprite_order = NULL;
	if (cub->sprite_distance != NULL)
		free(cub->sprite_distance);
	cub->sprite_distance = NULL;
	if (cub->sprt != NULL)
		free(cub->sprt);
	cub->sprt = NULL;
	if (cub->data.img.img_ptr != NULL)
		mlx_destroy_image(cub->data.mlx_ptr, cub->data.img.img_ptr);
	cub->data.img.img_ptr = NULL;
	if (cub->data.win_ptr != NULL)
		mlx_destroy_window(cub->data.mlx_ptr, cub->data.win_ptr);
	cub->data.win_ptr = NULL;
}

int			free_and_destroy(t_cub *cub)
{
	int		i;

	i = -1;
	if (cub->game.world_map != NULL)
	{
		while (++i < cub->state.height)
		{
			free(cub->game.world_map[i]);
			cub->game.world_map[i] = NULL;
		}
		free(cub->game.world_map);
		cub->game.world_map = NULL;
	}
	i = -1;
	while (++i < 4)
	{
		if (cub->texture[i].path != NULL)
			free(cub->texture[i].path);
		cub->texture[i].path = NULL;
	}
	free_buffer(cub);
	free_and_destroy2(cub);
	exit(0);
}
