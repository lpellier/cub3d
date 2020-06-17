#include "cub3d.h"

void minimap(t_cub *cub) {
	drawMinimap(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, cub->minimap.img_ptr, 0, 0);
}

void raycasting(t_cub *cub)
{
	
    for (int x = 0; x < WIN_WIDTH; x++)
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

		if (side == 0)
			perpWallDist = (mapX - cub->state.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub->state.posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int color;
		if (cub->game.worldMap[mapX][mapY] == 1)
			color = 16776960;
        if (side == 1) 
            color /= 2;
		putVerticalLineToImage(&cub->data, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, cub->data.img.img_ptr, 0, 0);
	minimap(cub);
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
}