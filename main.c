#include "cub3d.h"

int				events(int keyCode, void *param) {
	t_cub *cub;
	
	cub = (t_cub *)param;
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
	
	if (keyCode == KEY_ESC) {
		int i = 0;
		free(cub->game.worldMap);
		mlx_destroy_image(cub->data.mlx_ptr, cub->data.img.img_ptr);
		mlx_destroy_window(cub->data.mlx_ptr, cub->data.win_ptr);
		exit(0);
	}
	else if (keyCode == KEY_W) 
		moveForward(cub);
	else if (keyCode == KEY_S) 
		moveBackwards(cub);
	else if (keyCode == KEY_A) 
		strafeLeft(cub);
	else if (keyCode == KEY_D) 
		strafeRight(cub);
	else if (keyCode == KEY_RIGHT)
		rotateRight(cub);
	else if (keyCode == KEY_LEFT)
		rotateLeft(cub);
	raycasting(cub);
	return (0);
}

int			exitWdw(int event, void *param) {
	(void) param;
	(void) event;
	exit(0);
}

void getPos(int x, int y, char orientation, t_state *state) {
	state->posX = y + 0.5;
	state->posY = x + 0.5;
	orientation -= 48;
	if (orientation == 30) { // N
		state->dirX = -1;
		state->dirY = 0;
		state->planeX = 0;
		state->planeY = 0.66;
	}
	else if (orientation == 21) { // E
		state->dirX = 0;
		state->dirY = 1;
		state->planeX = 0.66;
		state->planeY = 0;
	}
	else if (orientation == 35) { // S
		state->dirX = 1;
		state->dirY = 0;
		state->planeX = 0;
		state->planeY = -0.66;
	}
	else if (orientation == 39) { // W
		state->dirX = 0;
		state->dirY = -1;
		state->planeX = -0.66;
		state->planeY = 0;
	}
}

int				*strto_intp(char *str, int height, t_state *state)
{
	int		i;
	int count;
	int		*map;
	int len = ft_strlen(str);

	state->heightWidth[height] = len;
	if (len > state->width)
		state->width = len;
	if (!(map = malloc(sizeof(int) * len)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ') {
			map[i] = 1;
		}
		else if (str[i] - 48 > 2) {
			map[i] = 0;
			
			getPos(i, height, str[i], state);
		}
		else
		{
			map[i] = str[i] - 48;
		}
		printf("%d ", map[i]);
		state->cellnbr++;
		i++;
	}
	free(str);
	printf("\n");
	return (map);
}

void				getMap(t_cub *cub)
{
	int				fd;
	int				height;
	int				**map;
	char			*line;

	line = NULL;
	height = 1;
	fd = open("shortmap.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		free(line);
		height++;
	}
	free(line);
	close(fd);
	if (!(cub->state.heightWidth = malloc(sizeof(int) * height)))
		return ;
	cub->state.height = height;
	cub->state.width = 0;
	cub->state.cellnbr = 0;
	fd = open("shortmap.cub", O_RDONLY);
	line = NULL;
	if (!(map = malloc(sizeof(int *) * height)))
		return ;
	height = 0;
	while (get_next_line(fd, &line))
	{
		map[height] = strto_intp(line, height, &cub->state);
		height++;
	}
	close(fd);
	map[height] = strto_intp(line, height, &cub->state);
	cub->game.worldMap = map;
	printf("height = %d && width = %d\n", cub->state.height, cub->state.width);
	return ;
}

void initState(t_cub *cub) {
	cub->state.time = (double)clock();
	cub->state.oldTime = 0;
}

int main(void)
{
	t_cub cub;
	// t_tex tex;

	if ((cub.data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((cub.data.win_ptr = mlx_new_window(cub.data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d")) == NULL)
		return (EXIT_FAILURE);

	// tex.width = tex.height = 10;
	initState(&cub);
	getMap(&cub);


	cub.minimap.width = cub.minimap.height = 300;
	cub.minimap.img_ptr = mlx_new_image(cub.data.mlx_ptr, cub.minimap.width, cub.minimap.height);
	cub.minimap.data = (int *)mlx_get_data_addr(cub.minimap.img_ptr, &cub.minimap.bpp, &cub.minimap.size_l, &cub.minimap.endian);

	cub.data.img.img_ptr = mlx_new_image(cub.data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cub.data.img.data = (int *)mlx_get_data_addr(cub.data.img.img_ptr, &cub.data.img.bpp, &cub.data.img.size_l, &cub.data.img.endian);
	
	
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", cub.state.dirX, cub.state.dirY, cub.state.posX, cub.state.posY);
	raycasting(&cub);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, mlx_xpm_file_to_image(data.mlx_ptr, "textures/eagle.xpm", &tex.width, &tex.height), 100, 100);
	mlx_hook(cub.data.win_ptr, 17, 0, exitWdw, NULL);
	mlx_hook(cub.data.win_ptr, 2, 1L << 0, events, &cub);
	mlx_loop(cub.data.mlx_ptr);
	return (EXIT_SUCCESS);
}
