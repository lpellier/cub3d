#include "cub3d.h"

void		moveForward(t_cub *cub) {
	if (cub->state.posX + cub->state.dirX * MOVE_SPEED >= 0) {
			if(cub->game.worldMap[(int)(cub->state.posX + cub->state.dirX * MOVE_SPEED)][(int)cub->state.posY] == 0) 
				cub->state.posX += cub->state.dirX * MOVE_SPEED;
		}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY + cub->state.dirY * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.dirY * MOVE_SPEED)] == 0)
			cub->state.posY += cub->state.dirY * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		moveBackwards(t_cub *cub) {
	if (cub->state.posX - cub->state.dirX * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.dirX * MOVE_SPEED)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.dirX * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY - cub->state.dirY * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.dirY * MOVE_SPEED)] == 0)
			cub->state.posY -= cub->state.dirY * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		strafeLeft(t_cub *cub) {
	if (cub->state.posX - cub->state.planeX * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.planeX * MOVE_SPEED)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.planeX * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY - cub->state.planeY * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.planeY * MOVE_SPEED)] == 0)
			cub->state.posY -= cub->state.planeY * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		strafeRight(t_cub *cub) {
	if (cub->state.posX + cub->state.planeX * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX + cub->state.planeX * MOVE_SPEED)][(int)cub->state.posY] == 0) 
			cub->state.posX += cub->state.planeX * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY + cub->state.planeY * MOVE_SPEED >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.planeY * MOVE_SPEED)] == 0)
			cub->state.posY += cub->state.planeY * MOVE_SPEED;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

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