#include "../cub3d.h"

int		framer(clock_t t, t_cub *cub)
{
	double	time_taken;
	double	spf;
	char	*fps;

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
	// printf("%s\n", fps);
	mlx_string_put(cub->data.mlx_ptr, cub->data.win_ptr,
			cub->data.img.width - (cub->data.img.width / 8),
			cub->data.img.height / 16, 255101, fps);
	free(fps);
	return (0);
}

int		freeAndDestroy(t_cub *cub) {
	int i = -1;

	while (++i < cub->state.height)
		free(cub->game.worldMap[i]);
	free(cub->game.worldMap);
	// free(cub->data.mapPath);
	i = -1;
	while (++i < 4)
		free(cub->texture[i].path);
	i = -1;
	while (++i < cub->data.img.height)
		free(cub->buffer[i]);
	free(cub->buffer);
	mlx_destroy_image(cub->data.mlx_ptr, cub->data.img.img_ptr);
	mlx_destroy_window(cub->data.mlx_ptr, cub->data.win_ptr);
	exit(0);
}

int			update(t_cub *cub) {
	int upd = 0;

	if (cub->game.keys[KEY_W] && (upd = 1)) 
		moveForward(cub);
	else if (cub->game.keys[KEY_S] && (upd = 1)) 
		moveBackwards(cub);
	if (cub->game.keys[KEY_A] && (upd = 1)) 
		strafeLeft(cub);
	else if (cub->game.keys[KEY_D] && (upd = 1)) 
		strafeRight(cub);
	if (cub->game.keys[KEY_RIGHT] && (upd = 1))
		rotateRight(cub);
	else if (cub->game.keys[KEY_LEFT] && (upd = 1))
		rotateLeft(cub);
	if (upd) {
		raycasting(cub);
		framer(cub->t, cub);
	}
	return (0);
}

int				release(int keyCode, void *param) {
	t_cub *cub;

	cub = (t_cub *)param;

	cub->game.keys[keyCode] = 0;
	return (0);
}

int				events(int keyCode, void *param) {
	t_cub *cub;

	cub = (t_cub *)param;
	cub->t = clock();
	
	if (keyCode == KEY_ESC)
		freeAndDestroy(cub);
	if (keyCode == KEY_W) 
		cub->game.keys[keyCode] = 1;  // moveForward(cub);
	else if (keyCode == KEY_S) 
		cub->game.keys[keyCode] = 1;  // moveBackwards(cub);
	if (keyCode == KEY_A) 
		cub->game.keys[keyCode] = 1;  // strafeLeft(cub);
	else if (keyCode == KEY_D) 
		cub->game.keys[keyCode] = 1;  // strafeRight(cub);
	if (keyCode == KEY_RIGHT)
		cub->game.keys[keyCode] = 1;  // rotateRight(cub);
	else if (keyCode == KEY_LEFT)
		cub->game.keys[keyCode] = 1;  // rotateLeft(cub);
	return (0);
}

int			exitWdw(int event, void *param) {
	(void) event;
	t_cub *cub = (t_cub *)param;
	
	return(freeAndDestroy(cub));
}

void loop(t_cub *cub) {
	raycasting(cub);
	mlx_hook(cub->data.win_ptr, 17, 0, exitWdw, cub);
	mlx_hook(cub->data.win_ptr, 2, 1L << 0, events, cub);
	mlx_hook(cub->data.win_ptr, 3, 1L << 0, release, cub);
	mlx_loop_hook(cub->data.mlx_ptr, update, cub);
	mlx_loop(cub->data.mlx_ptr);
}