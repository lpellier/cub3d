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
			// printf("%d ",cub->buffer[i][j]);
			putPixel(&cub->data.img, j, i, cub->buffer[i][j]);
			j++;
		}
		// printf("\n");
		i++;
	}
}

// NOT SO USED FUNCTIONS

void putSquare(t_img *img, int x, int y, int width, int height, unsigned int color) {
	int i = x;
	int j;
	while (i < width + x) {
		j = y;
		while (j < height + y) {
			putPixel(img, i, j, color);
			j++;
		}
		i++;
	}
	// printf("%d %d\n", x, y);
}
