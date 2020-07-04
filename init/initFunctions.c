#include "../cub3d.h"

int initBuffer(t_cub *cub) {
	if (!(cub->buffer = malloc(sizeof(int *) * cub->data.img.height)))
		return (0);
	int i = -1;
	while (++i < cub->data.img.height)
		if (!(cub->buffer[i] = malloc(sizeof(int) * cub->data.img.width)))
			return (0);
	if (!(cub->zBuffer = malloc(sizeof(double) * cub->data.img.width)))
		return (0);
	return (1);
}

void initState(t_cub *cub) {
	cub->state.time = (double)clock();
	cub->state.oldTime = 0;

	cub->state.width = 0;
	cub->state.height = 0;

	cub->numSprites = 0;
	cub->spriteIndex = 0;
	int i = -1;
	while (++i < 66000)
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

int getSprite(t_cub *cub, int index) {
	t_img *a = &cub->sprite[index];
	if (!(a->img_ptr = mlx_xpm_file_to_image(cub->data.mlx_ptr, a->path, &a->width, &a->height)))
		return (0);
	if (!(a->data = malloc(sizeof(unsigned int) * a->width * a->height)))
		return (0);
	a->data = (unsigned int *)mlx_get_data_addr(a->img_ptr, &a->bpp, &a->size_l, &a->endian);
	return (1);
}

int getTexSprite(t_cub *cub) {
	int i;
	
	i = -1;
	while (++i < 4) {	
		if (!getTexture(cub, i)) {
			printf("Texture Error\n");
			return (0);
		}
	}
	i = -1;
	while (++i < 3) {
		if (!getSprite(cub, i))
		{
			printf("Sprite Error\n");
			return (0);
		}
	}
	return (1);
}