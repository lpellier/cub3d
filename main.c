#include "cub3d.h"

int main(int ac, char **av)
{
	t_cub cub;
	int screenX, screenY;
	char *mapPath;

	initState(&cub);
	// if (ac != 2) {
	// 	printf("arg error\n");
	// 	return (0);
	// }
	mapPath = ft_strdup(av[1]);
	if (!fileParsing(&cub, mapPath))
	{
		printf("Parsing Error\n");
		exit(0);
	}
	printf("floor = %u ceiling = %u\n", cub.floorColor, cub.ceilColor);
	if (!initBuffer(&cub))
		return (0);
	if ((cub.data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	mlx_get_screen_size(cub.data.mlx_ptr, &screenX, &screenY);
	if (cub.data.img.width > screenX)
		cub.data.img.width = screenX;
	if (cub.data.img.height > screenY)
		cub.data.img.height = screenY;
	if ((cub.data.win_ptr = mlx_new_window(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height, "cub3d")) == NULL)
		return (0);
	
	printf("screenX = %d && screenY = %d\n", screenX, screenY);
	printf("numSprites = %d\n", cub.numSprites);
	if (!getTexSprite(&cub))
		return (0);
	int i = -1;
	while (++i < cub.numSprites) {
		printf("index : %d, posX = %f, posY = %f, path = %s, height = %d, width = %d\n", \
		i, cub.sprites[i].posX, cub.sprites[i].posY, cub.sprites[i].texture->path, cub.sprites[i].texture->height, cub.sprites[i].texture->width);
	}
	// cub.minimap.width = cub.minimap.height = 300;
	// cub.minimap.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.minimap.width, cub.minimap.height);
	// cub.minimap.data = (int *)mlx_get_data_addr(cub.minimap.img_ptr, &cub.minimap.bpp, &cub.minimap.size_l, &cub.minimap.endian);

	cub.data.img.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height);
	cub.data.img.data = (unsigned int *)mlx_get_data_addr(cub.data.img.img_ptr, &cub.data.img.bpp, &cub.data.img.size_l, &cub.data.img.endian);
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", cub.state.dirX, cub.state.dirY, cub.state.posX, cub.state.posY);
	raycasting(&cub);
	loop(&cub);
	return (1);
}
