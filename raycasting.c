#include "cub3d.h"

void raycasting(data_t data, state_t *state, int **worldMap)
{
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.data = (int *)mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.size_l, &data.img.endian);
    for (int x = 0; x < WIN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIN_WIDTH - 1;
		double rayDirX =state->dirX + state->planeX * cameraX;
		double rayDirY = state->dirY + state->planeY * cameraX;

		int mapX = (int)state->posX;
		int mapY = (int)state->posY;

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
			sideDistX = (state->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - state->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (state->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - state->posY) * deltaDistY;
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
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - state->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - state->posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 16776960;
        if (side == 1) 
            color /= 2;
		// printf("drawStart[%d] == %d && drawEnd[%d] == %d && color == %d && worldMap[%d][%d] == %d && stepX == %d && stepY == %d\n", \
		x, drawStart, x, drawEnd, color, mapX, mapY, worldMap[mapX][mapY], stepX, stepY);
		// drawVerticalLine(data, x, drawStart, drawEnd, color);
		putVerticalLineToImage(&data, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);
	// state->oldTime = state->time;
	// state->time = (double)clock();
	// double frameTime = (state->time - state->oldTime) / 1000.0;
	
	// double moveSpeed = frameTime * 5.0;
	// double rotationSpeed = frameTime * 3.0;
	// printf("%f\n", frameTime);
	// movePlayer();
}