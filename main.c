#include "cub3d.h"

int				events(int keyCode, void *param) {
	cub_t *cub;
	
	cub = (cub_t *)param;
	// cub->state.oldTime = cub->state.time;
	// cub->state.time = (double)clock();
	// double frameTime = (cub->state.time - cub->state.oldTime) / 1000.0;
	double moveSpeed = 0.2;
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
		raycasting(cub->data, &cub->state, cub->game.worldMap, 800, 640);
	}
	
	return (0);
}

int			exitWdw(int event, void *param) {
	(void) param;
	(void) event;
	exit(0);
}

int				*strto_intp(char *str)
{
	int		i;
	int		*map;

	if (!(map = malloc(sizeof(int) * ft_strlen(str))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		map[i] = str[i] - 48;
		i++;
	}
	return (map);
}

void				getMap(game_t *game)
{
	int				fd;
	int				height;
	int				**map;
	char			*line;

	line = NULL;
	height = 0;
	fd = open("testmap.cub", O_RDONLY);
	if (!(map = malloc(sizeof(int *) * 5)))
		return ;
	while (get_next_line(fd, &line))
	{
		map[height] = strto_intp(line);
		height++;
	}
	game->mapWidth = ft_strlen(line);
	game->mapHeight = height + 1;
	map[height] = strto_intp(line);
	game->worldMap = map;
	return ;
}

void getPos(game_t game, state_t *state) {
	int i = 0;
	while (i < game.mapHeight) {
		int j = 0;
		while (j < game.mapWidth) {
			if (game.worldMap[i][j] > 2) {
				state->posX = i;
				state->posY = j;
				if (game.worldMap[i][j] == 30) { // N
					state->dirX = 0;
					state->dirY = 1;
				}
				else if (game.worldMap[i][j] == 21) { // E
					state->dirX = 1;
					state->dirY = 0;
				}
				else if (game.worldMap[i][j] == 35) { // S
					state->dirX = 0;
					state->dirY = -1;
				}
				else if (game.worldMap[i][j] == 39) { // W
					state->dirX = -1;
					state->dirY = 0;
				}
			}
			j++;
		}
		i++;
	}
	printf("dirX = %f && dirY == %f\nposX = %f && posY = %f\n", state->dirX, state->dirY, state->posX, state->posY);
}

void initState(game_t game, state_t *state) {
    getPos(game, state);
	state->planeX = 0;
	state->planeY = 0.66;
	state->time = (double)clock();
	state->oldTime = 0;
}

int main(void)
{
	data_t		data;
	game_t		game;
	state_t state;
	cub_t cub;
	int			width;
	int			height;

	width = 800;
	height = 640;
	getMap(&game);
	initState(game, &state);
	// TEST
	int i = 0;
	int j;
	while (i < game.mapHeight)
	{
		j = 0;
		while (j < game.mapWidth)
		{
			printf("%d	", game.worldMap[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("Height = %d\n", game.mapHeight);
	printf("Width = %d\n", game.mapWidth);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.win_ptr = mlx_new_window(data.mlx_ptr, width, height, "cub3d")) == NULL)
		return (EXIT_FAILURE);

	
	cub.data = data;
	cub.game = game;
	cub.state = state;
	raycasting(cub.data, &cub.state, cub.game.worldMap, 800, 640);
	mlx_key_hook(data.win_ptr, events, &cub);
	mlx_hook(data.win_ptr, 17, 0, exitWdw, NULL);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
