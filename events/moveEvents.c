#include "../cub3d.h"

void		moveForward(t_cub *cub) {
	if (cub->state.posX + cub->state.dirX * MOV >= 0) {
			if(cub->game.worldMap[(int)(cub->state.posX + cub->state.dirX * MOV)][(int)cub->state.posY] == 0) 
				cub->state.posX += cub->state.dirX * MOV;
	}
	if (cub->state.posY + cub->state.dirY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.dirY * MOV)] == 0)
			cub->state.posY += cub->state.dirY * MOV;
	}
}

void		moveBackwards(t_cub *cub) {
	if (cub->state.posX - cub->state.dirX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.dirX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.dirX * MOV;
	}
	if (cub->state.posY - cub->state.dirY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.dirY * MOV)] == 0)
			cub->state.posY -= cub->state.dirY * MOV;
	}
}

void		strafeLeft(t_cub *cub) {
	if (cub->state.posX - cub->state.planeX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX - cub->state.planeX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX -= cub->state.planeX * MOV;
	}
	if (cub->state.posY - cub->state.planeY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.planeY * MOV)] == 0)
			cub->state.posY -= cub->state.planeY * MOV;
	}
}

void		strafeRight(t_cub *cub) {
	if (cub->state.posX + cub->state.planeX * MOV >= 0) {
		if(cub->game.worldMap[(int)(cub->state.posX + cub->state.planeX * MOV)][(int)cub->state.posY] == 0) 
			cub->state.posX += cub->state.planeX * MOV;
	}
	if (cub->state.posY + cub->state.planeY * MOV >= 0) {
		if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.planeY * MOV)] == 0)
			cub->state.posY += cub->state.planeY * MOV;
	}
}