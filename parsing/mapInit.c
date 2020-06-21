#include "../cub3d.h"

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
		if (str[i] == ' ')
			map[i] = 1;
		else if (str[i] > '2') {
			map[i] = 0;
			getPos(i, height, str[i], state);
		}
		else if (str[i] == '1')
			map[i] = 1;
		else if (str[i] == '0')
			map[i] = 0;
		else
			printf("Error\n");
		
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
    int             count_h;
	int				**map;
	char			*line;

	line = NULL;
    count_h = 0;
	if (!(cub->state.heightWidth = malloc(sizeof(int) * cub->state.height)))
		return ;
	cub->state.width = 0;
	cub->state.cellnbr = 0;
	fd = open("maps/testmap.cub", O_RDONLY);
	line = NULL;
	if (!(map = malloc(sizeof(int *) * cub->state.height)))
		return ;
	while (get_next_line(fd, &line))
	{
		map[count_h] = strto_intp(line, count_h, &cub->state);
		count_h++;
	}
	close(fd);
	map[count_h] = strto_intp(line, count_h, &cub->state);
	cub->game.worldMap = map;
	printf("height = %d && width = %d\n", cub->state.height, cub->state.width);
	return ;
}