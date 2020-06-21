#include "../cub3d.h"

// USED FUNCTIONS

void putPixel(t_img *img, int x, int y, unsigned int color) {
	img->data[y * img->width + x] = color;
}

void drawBuffer(t_cub *cub) {
	int i = 0;
	int j;
	while (i < WIN_HEIGHT) {
		j = 0;
		while (j < WIN_WIDTH) {
			putPixel(&cub->data.img, j, i, cub->buffer[i][j]);
			j++;
		}
		i++;
	}
}

// NOT SO USED FUNCTIONS

void putVerticalLineToImage(t_data *data, int x, int drawStart, int drawEnd, unsigned int color) {
	int count_h = -1;
	while (++count_h < WIN_HEIGHT) {
		if (count_h < drawStart) {
			data->img.data[count_h * WIN_WIDTH + x] = 1973790;
		}
		else if (count_h >= drawStart && count_h <= drawEnd) {
			data->img.data[count_h * WIN_WIDTH + x] = color;
		}
		else
		{
			data->img.data[count_h * WIN_WIDTH + x] = 1973820;
		}
	}
}

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

int *oneDArray(int **worldMap, t_state *state) {
	int *map;
	int count_h = 0;
	int count_w;
	int i = 0;

	// printf("number of cells = %d\n", state->cellnbr);
	if (!(map = malloc(sizeof(int) * state->cellnbr)))
		return (NULL);
	while (count_h < state->height) {
		count_w = 0;
		// printf("line : %d -> width = %d\n", count_h, state->heightWidth[count_h]);
		while (count_w < state->heightWidth[count_h]) {
			map[i] = worldMap[count_h][count_w];
			count_w++;
			i++;
		}
		// i++;
		count_h++;
	}
	return (map);
}

void drawMinimap(t_cub *cub) {
	int count_w = 0;
	int count_h = 0;
	int count = 0;
	int *map = oneDArray(cub->game.worldMap, &cub->state);
	unsigned int color = 8192000;
	int done = 0;

	cub->minimap.width -= cub->minimap.width % cub->state.width;
	cub->minimap.height -= cub->minimap.height % cub->state.height;

	int rX = cub->minimap.width / cub->state.width;
	int rY = cub->minimap.height / cub->state.height;
	// printf("rx = %d && ry = %d\n", rX, rY);
	while (count < cub->state.cellnbr)
	{
		if (map[count] == 1)
			color = 8192000;
		else
			color = 8224125;
		putSquare(&cub->minimap, count_w * rX, count_h * rY, rX, rY, color);
		putSquare(&cub->minimap, cub->state.posX * rX, cub->state.posY * rY, 10, 10, 51200);
		if (count_w < cub->state.heightWidth[count_h])
			count_w++;
		else {
			count_h++;
			count_w = 0;
		}
		// printf("count_w = %d && count_h = %d\n", count_w, count_h);
		count++;
	}
	
}
