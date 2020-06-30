#include "../cub3d.h"

int cmp(const void *left, const void *right) {
	t_sprt *a = (t_sprt *)left;
	t_sprt *b = (t_sprt *)right;

	if (b->dist < a->dist)
		return (1);
	else if (a->dist < b->dist)
		return (-1);
	else
		return ((a->order < b->order) - (b->order < a->order));
}

void sortSprites(t_cub *cub) {
	int i;

	i = -1;
	while (++i < cub->numSprites) {
		cub->sprt[i].dist = cub->spriteDistance[i];
		cub->sprt[i].order = cub->spriteOrder[i];	
	}
	qsort(cub->sprt, cub->numSprites, sizeof(t_sprt), cmp);
	i = -1;
	while (++i < cub->numSprites) {
		cub->spriteDistance[i] = cub->sprt[cub->numSprites - i - 1].dist;
		cub->spriteOrder[i] = cub->sprt[cub->numSprites - i - 1].order;
	}
}

void spriteCasting(t_cub *cub) 
{
	int i;

	i = -1;
	while (++i < cub->numSprites) {
		cub->spriteOrder[i] = i;
		cub->spriteDistance[i] = ((cub->state.posX - cub->sprites[i].posX) * (cub->state.posX - cub->sprites[i].posX) \
		+ (cub->state.posY - cub->sprites[i].posY) * (cub->state.posY - cub->sprites[i].posY));
	}
	sortSprites(cub);
	i = -1;
	// printf("player pos : x = %f, y = %f\n", cub->state.posX, cub->state.posY);
	while (++i < cub->numSprites)
	{
		double spriteX = cub->sprites[cub->spriteOrder[i]].posX - cub->state.posX;
		double spriteY = cub->sprites[cub->spriteOrder[i]].posY - cub->state.posY;
		// printf("i = %d && order = %d\n", i, cub->spriteOrder[i]);
		// printf("spriteX = %f, spriteY = %f\n", spriteX, spriteY);
		// printf("x = %f && y = %f\n\n", cub->sprites[cub->spriteOrder[i]].posX, cub->sprites[cub->spriteOrder[i]].posY);
		double invDet = 1.0 / (cub->state.planeX * cub->state.dirY - cub->state.dirX * cub->state.planeY);

		double transformX = invDet * (cub->state.dirY * spriteX - cub->state.dirX * spriteY);
		double transformY = invDet * (-cub->state.planeY * spriteX + cub->state.planeX * spriteY);
		// printf("%f %f\n", transformX, transformY);
		int spriteScreenX = (int)((cub->data.img.width / 2) * (1 + transformX / transformY));

		int spriteHeight = abs((int)(cub->data.img.height / (transformY)));

		int drawStartY = -spriteHeight / 2 + cub->data.img.height / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub->data.img.height / 2;
		if (drawEndY >= cub->data.img.height)
			drawEndY = cub->data.img.height - 1;
		
		int spriteWidth = abs((int)(cub->data.img.height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= cub->data.img.width)
			drawEndX = cub->data.img.width - 1;
		int stripe = drawStartX - 1;
		while (++stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * cub->sprites[cub->spriteOrder[i]].texture->width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < cub->data.img.width && transformY < cub->zBuffer[stripe])
			{
				int y = drawStartY - 1;
				while (++y < drawEndY)
				{
					int d = (y) * 256 - cub->data.img.height * 128 + spriteHeight * 128;
					int texY = ((d * cub->sprites[cub->spriteOrder[i]].texture->height) / spriteHeight) / 256;
					int color = cub->sprites[cub->spriteOrder[i]].texture->data[cub->sprites[cub->spriteOrder[i]].texture->width * texY + texX];
					if ((color & 0x00FFFFFF) != 0)
						cub->buffer[y][stripe] = color;
				}
			}
		}
	}
}

void raycasting(t_cub *cub)
{
	int x = -1;
    while (++x < cub->data.img.width)
	{
		double cameraX = 2 * x / (double)cub->data.img.width - 1;
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
			if (cub->game.worldMap[mapX][mapY] == 1) 
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
		int lineHeight = (int)(cub->data.img.height / perpWallDist);

		int drawStart = -lineHeight / 2 + cub->data.img.height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->data.img.height / 2;
		if (drawEnd >= cub->data.img.height)
			drawEnd = cub->data.img.height - 1;

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
		double texPos = (drawStart - cub->data.img.height / 2 + lineHeight / 2) * step;
		for (int y = 0; y < drawStart; y++) 
		{
			color = cub->ceilColor;
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
			if (perpWallDist > 5) color = (color >> 1) & 8355711;
			cub->buffer[y][x] = color;
		}
		for (int y = drawEnd; y < cub->data.img.height; y++) 
		{
			color = cub->floorColor;
			cub->buffer[y][x] = color;
		}
		cub->zBuffer[x] = perpWallDist;
	}
	spriteCasting(cub);
	drawBuffer(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, cub->data.img.img_ptr, 0, 0);
}
