#include "../cub3d.h"

int initBuffer(t_cub *cub) {
	if (!(cub->buffer = malloc(sizeof(int *) * cub->data.img.height)))
		return (0);
	int i = -1;
	while (++i < cub->data.img.height)
		if (!(cub->buffer[i] = malloc(sizeof(int) * cub->data.img.width)))
			return (0);
	return (1);
}

void initState(t_cub *cub) {
	cub->state.time = (double)clock();
	cub->state.oldTime = 0;

	cub->state.width = 0;
	cub->state.height = 0;

	int i = -1;
	while (++i < 6600)
		cub->game.keys[i] = 0;
}