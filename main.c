#include "cub3d.h"

void initState(t_cub *cub) {
	cub->state.time = (double)clock();
	cub->state.oldTime = 0;

	cub->state.width = 0;
	cub->state.height = 0;

	int i = -1;
	while (++i < 6600)
		cub->game.keys[i] = 0;
}

int getTexture(t_cub *cub, int index) {
	t_img *a = &cub->texture[index];
	if (!(a->img_ptr = mlx_xpm_file_to_image(cub->data.mlx_ptr, a->path, &a->width, &a->height)))
		return (0);
	if (!(a->data = malloc(sizeof(unsigned int) * a->width * a->height)))
		return (0);
	a->data = (unsigned int *)mlx_get_data_addr(a->img_ptr, &a->bpp, &a->size_l, &a->endian);
	return (1);
}

int initBuffer(t_cub *cub) {
	if (!(cub->buffer = malloc(sizeof(int *) * cub->data.img.height)))
		return (0);
	int i = -1;
	while (++i < cub->data.img.height)
		if (!(cub->buffer[i] = malloc(sizeof(int) * cub->data.img.width)))
			return (0);
	return (1);
}

int main(void)
{
	t_cub cub;

	initState(&cub);
	if (!fileParsing(&cub))
	{
		printf("Parsing Error\n");
		exit(0);
	}
	printf("floor = %u ceiling = %u\n", cub.floorColor, cub.ceilColor);
	if (!initBuffer(&cub))
		return (0);
	if ((cub.data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((cub.data.win_ptr = mlx_new_window(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height, "cub3d")) == NULL)
		return (0);

	int i = -1;
	while (++i < 4) {	
		if (!getTexture(&cub, i)) {
			printf("Texture Error\n");
			return (0);
		}
	}

	// cub.minimap.width = cub.minimap.height = 300;
	// cub.minimap.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.minimap.width, cub.minimap.height);
	// cub.minimap.data = (int *)mlx_get_data_addr(cub.minimap.img_ptr, &cub.minimap.bpp, &cub.minimap.size_l, &cub.minimap.endian);

	cub.data.img.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height);
	cub.data.img.data = (unsigned int *)mlx_get_data_addr(cub.data.img.img_ptr, &cub.data.img.bpp, &cub.data.img.size_l, &cub.data.img.endian);
	
	
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", cub.state.dirX, cub.state.dirY, cub.state.posX, cub.state.posY);
	raycasting(&cub);

	mlx_hook(cub.data.win_ptr, 17, 0, exitWdw, &cub);
	mlx_hook(cub.data.win_ptr, 2, 1L << 0, events, &cub);
	mlx_hook(cub.data.win_ptr, 3, 1L << 0, release, &cub);
	mlx_loop_hook(cub.data.mlx_ptr, update, &cub);
	mlx_loop(cub.data.mlx_ptr);
	return (1);
}
