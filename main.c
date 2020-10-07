#include "cub3d.h"

int put_error(char *str) 
{
	printf("Error\n");
	printf("%s\n", str);
	return (0);
}

int main(int ac, char **av)
{
	t_cub cub;
	int screen_x, screen_y;
	char *map_path;

	init_state(&cub);
	if (ac != 2) 
	{
		put_error("arg error");
		exit(0);
	}
	map_path = ft_strdup(av[1]);
	if (!file_parsing(&cub, map_path))
		exit(0);
	if (!init_buffer(&cub))
		return (0);
	if ((cub.data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	mlx_get_screen_size(cub.data.mlx_ptr, &screen_x, &screen_y);
	if (cub.data.img.width > screen_x)
		cub.data.img.width = screen_x;
	if (cub.data.img.height > screen_y)
		cub.data.img.height = screen_y;
	if ((cub.data.win_ptr = mlx_new_window(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height, "cub3d")) == NULL)
		return (0);
	if (!get_tex_sprite(&cub))
		return (0);
	cub.data.img.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.data.img.width, cub.data.img.height);
	cub.data.img.data = (unsigned int *)mlx_get_data_addr(cub.data.img.img_ptr, &cub.data.img.bpp, &cub.data.img.size_l, &cub.data.img.endian);
	raycasting(&cub);
	loop(&cub);
	return (1);
}
