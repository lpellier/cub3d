#include "cub3d.h"

void raycasting(data_t data, state_t *state, int **worldMap, int width, int height)
{
    for (int x = 0; x < width; x++)
	{
		double cameraX = 2 * x / (double)width - 1;
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
		int lineHeight = (int)(height / perpWallDist);

		int drawStart = -lineHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;

		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 16776960;	
		else if (worldMap[mapX][mapY] == 2)
			color = 1000000;
        if (side == 1) 
            color = color / 2;
		// printf("drawStart[%d] == %d && drawEnd[%d] == %d && color == %d && worldMap[%d][%d] == %d && stepX == %d && stepY == %d\n", \
		x, drawStart, x, drawEnd, color, mapX, mapY, worldMap[mapX][mapY], stepX, stepY);
		drawVerticalLine(data, x, drawStart, drawEnd, color);
	}
	state->oldTime = state->time;
	state->time = (double)clock();
	double frameTime = (state->time - state->oldTime) / 1000.0;
	
	double moveSpeed = frameTime * 5.0;
	double rotationSpeed = frameTime * 3.0;
	// printf("%f\n", frameTime);
	// movePlayer();
}