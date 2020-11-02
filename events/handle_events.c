/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:02:34 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/02 17:54:10 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		free_buffer(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->data.img.height)
		free(cub->buffer[i]);
	free(cub->buffer);
}

int			free_and_destroy(t_cub *cub)
{
	int		i;

	i = -1;
	while (++i < cub->state.height)
		free(cub->game.world_map[i]);
	free(cub->game.world_map);
	i = -1;
	while (++i < 4)
		free(cub->texture[i].path);
	free_buffer(cub);
	free(cub->z_buffer);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(cub->data.mlx_ptr, cub->texture[i].img_ptr);
	free(cub->sprite_order);
	free(cub->sprite_distance);
	free(cub->sprt);
	mlx_destroy_image(cub->data.mlx_ptr, cub->data.img.img_ptr);
	mlx_destroy_window(cub->data.mlx_ptr, cub->data.win_ptr);
	exit(0);
}

int			update(t_cub *cub)
{
	int		upd;

	upd = 0;
	if (cub->game.keys[KEY_W] && (upd = 1))
		move_forward(cub);
	else if (cub->game.keys[KEY_S] && (upd = 1))
		move_backwards(cub);
	if (cub->game.keys[KEY_A] && (upd = 1))
		strafe_left(cub);
	else if (cub->game.keys[KEY_D] && (upd = 1))
		strafe_right(cub);
	if (cub->game.keys[KEY_RIGHT] && (upd = 1))
		rotate_right(cub);
	else if (cub->game.keys[KEY_LEFT] && (upd = 1))
		rotate_left(cub);
	if (upd)
		raycasting(cub, 0);
	return (0);
}

int			release(int key_code, void *param)
{
	t_cub		*cub;

	cub = (t_cub *)param;
	cub->game.keys[key_code] = 0;
	return (0);
}

int			events(int key_code, void *param)
{
	t_cub		*cub;

	cub = (t_cub *)param;
	cub->t = clock();
	if (key_code == KEY_ESC)
		free_and_destroy(cub);
	if (key_code == KEY_W)
		cub->game.keys[key_code] = 1;
	else if (key_code == KEY_S)
		cub->game.keys[key_code] = 1;
	if (key_code == KEY_A)
		cub->game.keys[key_code] = 1;
	else if (key_code == KEY_D)
		cub->game.keys[key_code] = 1;
	if (key_code == KEY_RIGHT)
		cub->game.keys[key_code] = 1;
	else if (key_code == KEY_LEFT)
		cub->game.keys[key_code] = 1;
	return (0);
}
