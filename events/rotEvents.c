#include "../cub3d.h"

void		rotateLeft(t_cub *cub) {
	double oldDirX = cub->state.dirX;
	cub->state.dirX = cub->state.dirX * cos(ROT) - cub->state.dirY * sin(ROT);
	cub->state.dirY = oldDirX * sin(ROT) + cub->state.dirY * cos(ROT);
	double oldPlaneX = cub->state.planeX;
	cub->state.planeX = cub->state.planeX * cos(ROT) - cub->state.planeY * sin(ROT);
	cub->state.planeY = oldPlaneX * sin(ROT) + cub->state.planeY * cos(ROT);
}

void		rotateRight(t_cub *cub) {
	double oldDirX = cub->state.dirX;
	cub->state.dirX = cub->state.dirX * cos(-ROT) - cub->state.dirY * sin(-ROT);
	cub->state.dirY = oldDirX * sin(-ROT) + cub->state.dirY * cos(-ROT);
	double oldPlaneX = cub->state.planeX;
	cub->state.planeX = cub->state.planeX * cos(-ROT) - cub->state.planeY * sin(-ROT);
	cub->state.planeY = oldPlaneX * sin(-ROT) + cub->state.planeY * cos(-ROT);
}