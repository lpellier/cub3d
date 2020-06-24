#include "../cub3d.h"

void raycasting(t_cub *cub)
{
	int x = -1;
    while (++x < WIN_WIDTH)
	{
		double cameraX = 2 * x / (double)WIN_WIDTH - 1;
		double rayDirX = cub->state.dirX + cub->state.planeX * cameraX;
		double rayDirY = cub->state.dirY + cub->state.planeY * cameraX;

		int mapX = (int)cub->state.posX;
		int mapY = (int)cub->state.posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
      	double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->state.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->state.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->state.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->state.posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cub->game.worldMap[mapX][mapY] > 0) 
				hit = 1;
		}

		int texNum;

		if (side == 0) {
			perpWallDist = (mapX - cub->state.posX + (1 - stepX) / 2) / rayDirX;
			if (rayDirX > 0)
				texNum = 0; // SOUTH
			else
				texNum = 1; // NORTH
		}
		else {
			perpWallDist = (mapY - cub->state.posY + (1 - stepY) / 2) / rayDirY;
			if (rayDirY > 0)
				texNum = 2; // EAST
			else
				texNum = 3; // WEST
		}
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		unsigned int color;
		//texturing calculations

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = cub->state.posY + perpWallDist * rayDirY;
		else           wallX = cub->state.posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(cub->texture[texNum].width));
		if(side == 0 && rayDirX > 0) texX = cub->texture[texNum].width - texX - 1;
		if(side == 1 && rayDirY < 0) texX = cub->texture[texNum].width - texX - 1;
	
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * cub->texture[texNum].height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = 0; y < drawStart; y++) {
			color = 1973790;
			cub->buffer[y][x] = color;
		}
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (cub->texture[texNum].height - 1);
			texPos += step;
			color = cub->texture[texNum].data[cub->texture[texNum].height * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			cub->buffer[y][x] = color;
		}
		for (int y = drawEnd; y < WIN_HEIGHT; y++) {
			color = 1973820;
			cub->buffer[y][x] = color;
		}
		// if (cub->game.worldMap[mapX][mapY] == 1)
		// 	color = 16776960;
        // if (side == 1) 
        //     color /= 2;
		// putVerticalLineToImage(&cub->data, x, drawStart, drawEnd, color);
	}
	drawBuffer(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, cub->data.img.img_ptr, 0, 0);
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
}
