#include "../cub3d.h"

int		freeAndDestroy(t_cub *cub) {
	int i = -1;

	while (++i < cub->state.height)
		free(cub->game.worldMap[i]);
	free(cub->game.worldMap);
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
	if (upd)
		raycasting(cub);

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
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
	
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