#include "../cub3d.h"

void		moveForward(t_cub *cub) {
	if (cub->state.posX + cub->state.dirX * MOV >= 0) {
			if(cub->game.worldMap[(int)(cub->state.posX + cub->state.dirX * MOV)][(int)cub->state.posY] == 0) 
				cub->state.posX += cub->state.dirX * MOV;
		}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY + cub->state.dirY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.dirY * MOV)] == 0)
			cub->state.posY += cub->state.dirY * MOV;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		moveBackwards(t_cub *cub) {
	if (cub->state.posX - cub->state.dirX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.dirX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.dirX * MOV;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY - cub->state.dirY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.dirY * MOV)] == 0)
			cub->state.posY -= cub->state.dirY * MOV;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		strafeLeft(t_cub *cub) {
	if (cub->state.posX - cub->state.planeX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.planeX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.planeX * MOV;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY - cub->state.planeY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.planeY * MOV)] == 0)
			cub->state.posY -= cub->state.planeY * MOV;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}

void		strafeRight(t_cub *cub) {
	if (cub->state.posX + cub->state.planeX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX + cub->state.planeX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX += cub->state.planeX * MOV;
	}
	else
	{
		if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
			cub->state.posX = 0;
	}
	if (cub->state.posY + cub->state.planeY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.planeY * MOV)] == 0)
			cub->state.posY += cub->state.planeY * MOV;
	}
	else
	{
		if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
			cub->state.posY = 0;
	}
}