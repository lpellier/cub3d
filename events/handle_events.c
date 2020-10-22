/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:02:34 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/21 18:40:47 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			framer(clock_t t, t_cub *cub)
{
	double		time_taken;
	double		spf;
	char		*fps;

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	spf = 1.0 / FPS;
	if (time_taken < spf)
	{
		time_taken = spf;
		nanosleep(&(struct timespec){0, time_taken * 1000000000}, 0);
	}
	cub->data.time_taken = time_taken;
	fps = ft_itoa((int)(1.0 / time_taken));
	mlx_string_put(cub->data.mlx_ptr, cub->data.win_ptr,
			cub->data.img.width - (cub->data.img.width / 8),
			cub->data.img.height / 16, 255101, fps);
	free(fps);
	return (0);
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
	i = -1;
	while (++i < cub->data.img.height)
		free(cub->buffer[i]);
	free(cub->buffer);
	free(cub->z_buffer);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(cub->data.mlx_ptr, cub->texture[i].img_ptr);
	// i = -1;
	// while (++i < cub->num_sprites)
	// 	mlx_destroy_image(cub->data.mlx_ptr, cub->sprite[i].img_ptr);
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
	{
		raycasting(cub, 0);
		framer(cub->t, cub);
	}
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
