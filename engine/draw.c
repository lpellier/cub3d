#include "../cub3d.h"

// USED FUNCTIONS

void put_pixel(t_img *img, int x, int y, unsigned int color) {
	img->data[y * img->width + x] = color;
}

void draw_buffer(t_cub *cub) {
	int i = 0;
	int j;
	while (i < cub->data.img.height) {
		j = 0;
		while (j < cub->data.img.width) {
			put_pixel(&cub->data.img, j, i, cub->buffer[i][j]);
			j++;
		}
		i++;
	}
}

// NOT SO USED FUNCTIONS

void put_square(t_cub *cub, int x, int y, int width, int height, unsigned int color) {
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

void draw_minimap(t_cub *cub)
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
			if (cub->game.world_map[j][i] == 1)
				put_square(cub, (int)(i * resx), (int)(j * resy), resx, resy, WHITE);
			else if (cub->game.world_map[j][i] >= 2)
				put_square(cub, (int)(i * resx), (int)(j * resy), resx, resy, BLUE);
		}
	}
	put_square(cub, (int)(cub->state.pos_y * resx), (int)(cub->state.pos_x * resy), 10, 10, GREEN);
}