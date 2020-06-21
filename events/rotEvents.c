#include "../cub3d.h"

void		rotateLeft(t_cub *cub) {
	double oldDirX = cub->state.dirX;
	cub->state.dirX = cub->state.dirX * cos(ROT_SPEED) - cub->state.dirY * sin(ROT_SPEED);
	cub->state.dirY = oldDirX * sin(ROT_SPEED) + cub->state.dirY * cos(ROT_SPEED);
	double oldPlaneX = cub->state.planeX;
	cub->state.planeX = cub->state.planeX * cos(ROT_SPEED) - cub->state.planeY * sin(ROT_SPEED);
	cub->state.planeY = oldPlaneX * sin(ROT_SPEED) + cub->state.planeY * cos(ROT_SPEED);
}

void		rotateRight(t_cub *cub) {
	double oldDirX = cub->state.dirX;
	cub->state.dirX = cub->state.dirX * cos(-ROT_SPEED) - cub->state.dirY * sin(-ROT_SPEED);
	cub->state.dirY = oldDirX * sin(-ROT_SPEED) + cub->state.dirY * cos(-ROT_SPEED);
	double oldPlaneX = cub->state.planeX;
	cub->state.planeX = cub->state.planeX * cos(-ROT_SPEED) - cub->state.planeY * sin(-ROT_SPEED);
	cub->state.planeY = oldPlaneX * sin(-ROT_SPEED) + cub->state.planeY * cos(-ROT_SPEED);
}