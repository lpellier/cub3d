#include "cub3d.h"

int				events(int keyCode, void *param) {
	cub_t *cub;
	
	cub = (cub_t *)param;
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
	double moveSpeed = 0.2;
	double rotSpeed = 0.1;
	
	if (keyCode == KEY_ESC) {
		exit(0);
	}
	else if (keyCode == KEY_FORWARD) {
		if (cub->state.posX + cub->state.dirX * moveSpeed >= 0) {
			if(cub->game.worldMap[(int)(cub->state.posX + cub->state.dirX * moveSpeed)][(int)cub->state.posY] == 0) 
				cub->state.posX += cub->state.dirX * moveSpeed;
		}
		else
		{
			if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
				cub->state.posX = 0;
		}
		if (cub->state.posY + cub->state.dirY * moveSpeed >= 0) {
			if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY + cub->state.dirY * moveSpeed)] == 0)
				cub->state.posY += cub->state.dirY * moveSpeed;
		}
		else
		{
			if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
				cub->state.posY = 0;
		}
		printf("%f	%f\n", cub->state.posX, cub->state.posY);	
		raycasting(cub->data, &cub->state, cub->game.worldMap);
	}
	else if (keyCode == KEY_BACKWARD) {
		if (cub->state.posX - cub->state.dirX * moveSpeed >= 0) {
			if(cub->game.worldMap[(int)(cub->state.posX - cub->state.dirX * moveSpeed)][(int)cub->state.posY] == 0) 
				cub->state.posX -= cub->state.dirX * moveSpeed;
		}
		else
		{
			if(cub->game.worldMap[0][(int)cub->state.posY] == 0) 
				cub->state.posX = 0;
		}
		if (cub->state.posY - cub->state.dirY * moveSpeed >= 0) {
			if(cub->game.worldMap[(int)cub->state.posX][(int)(cub->state.posY - cub->state.dirY * moveSpeed)] == 0)
				cub->state.posY -= cub->state.dirY * moveSpeed;
		}
		else
		{
			if(cub->game.worldMap[(int)cub->state.posX][0] == 0)
				cub->state.posY = 0;
		}
		printf("%f	%f\n", cub->state.posX, cub->state.posY);	
		raycasting(cub->data, &cub->state, cub->game.worldMap);
	}
	else if (keyCode == KEY_RIGHT)
	{
		double oldDirX = cub->state.dirX;
		cub->state.dirX = cub->state.dirX * cos(-rotSpeed) - cub->state.dirY * sin(-rotSpeed);
		cub->state.dirY = oldDirX * sin(-rotSpeed) + cub->state.dirY * cos(-rotSpeed);
		double oldPlaneX = cub->state.planeX;
		cub->state.planeX = cub->state.planeX * cos(-rotSpeed) - cub->state.planeY * sin(-rotSpeed);
		cub->state.planeY = oldPlaneX * sin(-rotSpeed) + cub->state.planeY * cos(-rotSpeed);
		raycasting(cub->data, &cub->state, cub->game.worldMap);
	}
	else if (keyCode == KEY_LEFT)
	{
		double oldDirX = cub->state.dirX;
		cub->state.dirX = cub->state.dirX * cos(rotSpeed) - cub->state.dirY * sin(rotSpeed);
		cub->state.dirY = oldDirX * sin(rotSpeed) + cub->state.dirY * cos(rotSpeed);
		double oldPlaneX = cub->state.planeX;
		cub->state.planeX = cub->state.planeX * cos(rotSpeed) - cub->state.planeY * sin(rotSpeed);
		cub->state.planeY = oldPlaneX * sin(rotSpeed) + cub->state.planeY * cos(rotSpeed);
		raycasting(cub->data, &cub->state, cub->game.worldMap);
	}
	return (0);
}

int			exitWdw(int event, void *param) {
	(void) param;
	(void) event;
	exit(0);
}

void getPos(int x, int y, char orientation, state_t *state) {
	state->posX = y;
	state->posY = x;
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
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", state->dirX, state->dirY, state->posX, state->posY);
}

int				*strto_intp(char *str, int height, state_t *state)
{
	int		i;
	int count;
	int		*map;

	if (!(map = malloc(sizeof(int) * ft_strlen(str))))
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
		// printf("%d %c\n", i, str[i]);
		i++;
	}
	printf("\n");
	return (map);
}

void				getMap(game_t *game, state_t *state)
{
	int				fd;
	int				height;
	int				**map;
	char			*line;

	line = NULL;
	height = 0;
	fd = open("testmap.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		height++;
	}
	fd = open("testmap.cub", O_RDONLY);
	line = NULL;
	
	if (!(map = malloc(sizeof(int *) * height)))
		return ;
	height = 0;
	while (get_next_line(fd, &line))
	{
		map[height] = strto_intp(line, height, state);
		height++;
	}
	map[height] = strto_intp(line, height, state);
	game->worldMap = map;
	return ;
}



void initState(game_t game, state_t *state) {
	state->time = (double)clock();
	state->oldTime = 0;
}

int main(void)
{
	data_t		data;
	game_t		game;
	state_t state;
	cub_t cub;

	initState(game, &state);
	getMap(&game, &state);
	
	// TEST
	// int i = 0;
	// int j;
	// while (i < game.mapHeight)
	// {
	// 	j = 0;
	// 	while (j < game.mapWidth)
	// 	{
	// 		printf("%d	", game.worldMap[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// 	printf("\n");
	// }
	// printf("Height = %d\n", game.mapHeight);
	// printf("Width = %d\n", game.mapWidth);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d")) == NULL)
		return (EXIT_FAILURE);

	cub.data = data;
	cub.game = game;
	cub.state = state;
	raycasting(cub.data, &cub.state, cub.game.worldMap);
	// printf("test\n");
	mlx_hook(data.win_ptr, 17, 0, exitWdw, NULL);
	mlx_hook(data.win_ptr, 2, 1L << 0, events, &cub);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
