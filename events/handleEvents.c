#include "../cub3d.h"

int		freeAndDestroy(t_cub *cub) {
	int i = -1;

	while (++i < cub->state.height)
		free(cub->game.worldMap[i]);
	free(cub->game.worldMap);
	mlx_destroy_image(cub->data.mlx_ptr, cub->data.img.img_ptr);
	mlx_destroy_window(cub->data.mlx_ptr, cub->data.win_ptr);
	exit(0);
}

int				events(int keyCode, void *param) {
	t_cub *cub;
	
	cub = (t_cub *)param;
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
	
	if (keyCode == KEY_ESC)
		freeAndDestroy(cub);
	else if (keyCode == KEY_W) 
		moveForward(cub);
	else if (keyCode == KEY_S) 
		moveBackwards(cub);
	else if (keyCode == KEY_A) 
		strafeLeft(cub);
	else if (keyCode == KEY_D) 
		strafeRight(cub);
	else if (keyCode == KEY_RIGHT)
		rotateRight(cub);
	else if (keyCode == KEY_LEFT)
		rotateLeft(cub);
	raycasting(cub);
	return (0);
}

int			exitWdw(int event, void *param) {
	(void) event;
	t_cub *cub = (t_cub *)param;
	
	return(freeAndDestroy(cub));
}