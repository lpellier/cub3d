#include "../cub3d.h"

// USED FUNCTIONS

void putPixel(t_img *img, int x, int y, unsigned int color) {
	img->data[y * img->width + x] = color;
}

void drawBuffer(t_cub *cub) {
	int i = 0;
	int j;
	while (i < cub->data.img.height) {
		j = 0;
		while (j < cub->data.img.width) {
			putPixel(&cub->data.img, j, i, cub->buffer[i][j]);
			j++;
		}
		i++;
	}
}

// NOT SO USED FUNCTIONS

void putSquare(t_cub *cub, int x, int y, int width, int height, unsigned int color) {
	int i = y;
	int j;
	while (i < height + y) {
		j = x;
		while (j < width + x) {
			cub->buffer[i][j] = color;
			j++;
		}
		i++;
	}
}

void drawMinimap(t_cub *cub)
{
	int rx = cub->data.img.width / 3;
	int ry = cub->data.img.height / 3;
	int resx, resy;
	int i, j;

	i = j = -1;
	resx = rx / cub->state.width;
	resy = ry / cub->state.height;
	while (++i < cub->state.width)
	{
		j = -1;
		while (++j < cub->state.height) {
			if (cub->game.worldMap[j][i] == 1)
				putSquare(cub, (int)(i * resx), (int)(j * resy), resx, resy, WHITE);
			else if (cub->game.worldMap[j][i] >= 2)
				putSquare(cub, (int)(i * resx), (int)(j * resy), resx, resy, BLUE);
		}
	}
	putSquare(cub, (int)(cub->state.posY * resx), (int)(cub->state.posX * resy), 10, 10, GREEN);
}