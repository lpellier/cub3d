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

void getTexture(t_cub *cub, int index, char *path) {
	t_img *a = &cub->texture[index];
	a->img_ptr = mlx_xpm_file_to_image(cub->data.mlx_ptr, path, &a->width, &a->height);
	if (!(a->data = malloc(sizeof(unsigned int) * a->width * a->height)))
		return;
	a->data = (unsigned int *)mlx_get_data_addr(a->img_ptr, &a->bpp, &a->size_l, &a->endian);
}

int main(void)
{
	t_cub cub;

	if ((cub.data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((cub.data.win_ptr = mlx_new_window(cub.data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d")) == NULL)
		return (EXIT_FAILURE);

	initState(&cub);
	if (!fileParsing(&cub))
	{
		printf("Parsing Error\n");
		exit(0);
	}

	getTexture(&cub, 0,"textures/minecraft/cobblestone.xpm");  					// SOUTH
	getTexture(&cub, 1 ,"textures/minecraft/stone.xpm");						// NORTH
	getTexture(&cub, 2 ,"textures/minecraft/cracked_stone_bricks.xpm");		 	// EAST
	getTexture(&cub, 3 ,"textures/minecraft/chiseled_stone_bricks.xpm"); 	  	// WEST
	// for (int i = 0; i < cub.texture[0].width * cub.texture[0].height; i++)	
	// 	printf("index : %d -> color = %u\n", i, cub.texture[0].data[i]);

	// cub.minimap.width = cub.minimap.height = 300;
	// cub.minimap.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.minimap.width, cub.minimap.height);
	// cub.minimap.data = (int *)mlx_get_data_addr(cub.minimap.img_ptr, &cub.minimap.bpp, &cub.minimap.size_l, &cub.minimap.endian);

	cub.data.img.img_ptr = mlx_new_image(cub.data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cub.data.img.width = WIN_WIDTH;
	cub.data.img.height = WIN_HEIGHT;
	cub.data.img.data = (unsigned int *)mlx_get_data_addr(cub.data.img.img_ptr, &cub.data.img.bpp, &cub.data.img.size_l, &cub.data.img.endian);
	
	
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", cub.state.dirX, cub.state.dirY, cub.state.posX, cub.state.posY);
	raycasting(&cub);

	mlx_hook(cub.data.win_ptr, 17, 0, exitWdw, &cub);
	mlx_hook(cub.data.win_ptr, 2, 1L << 0, events, &cub);
	mlx_hook(cub.data.win_ptr, 3, 1L << 0, release, &cub);
	mlx_loop_hook(cub.data.mlx_ptr, update, &cub);
	mlx_loop(cub.data.mlx_ptr);
	return (EXIT_SUCCESS);
}
