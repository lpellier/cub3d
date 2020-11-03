/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:17:49 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 18:10:56 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			exit_wdw(int event, void *param)
{
	t_cub		*cub;

	(void)event;
	cub = (t_cub *)param;
	free_buffer(cub);
	exit(0);
}

void		loop(t_cub *cub)
{
	raycasting(cub, 0);
	mlx_hook(cub->data.win_ptr, 17, 1L << 17, exit_wdw, cub);
	mlx_hook(cub->data.win_ptr, 2, 1L << 0, events, cub);
	mlx_hook(cub->data.win_ptr, 3, 1L << 1, release, cub);
	mlx_loop_hook(cub->data.mlx_ptr, update, cub);
	mlx_loop(cub->data.mlx_ptr);
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
