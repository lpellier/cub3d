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

int				*strto_intp(char *str, int height, t_cub *cub)
{
	int		i;
	int count;
	int		*map;

	if (!(map = malloc(sizeof(int) * cub->state.width)))
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			map[i] = 1;
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W') {
			map[i] = 0;
			getPos(i, height, str[i], &cub->state);
		}
		else if (str[i] == '1')
			map[i] = 1;
		else if (str[i] == '0')
			map[i] = 0;
		else if (str[i] >= '2') {
			map[i] = str[i] - 48;
			cub->sprites[cub->spriteIndex].posX = i + 0.5;
			cub->sprites[cub->spriteIndex].posY = height + 0.5;
			cub->sprites[cub->spriteIndex].texture = &cub->sprite[str[i] - 48 - 2];
			cub->spriteIndex += 1;
		}
		else
			printf("Map Error\n");
		printf("%d ", map[i]);
	}
	free(str);
	while (i++ < cub->state.width) {
		map[i] = 1;
		printf("%d ", map[i]);
	}
	printf("\n");
	return (map);
}

int		lineIsMap(char *str) {
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str != '1')
		return (0);
	return (1);
}

void				getMap(t_cub *cub)
{
	int				fd;
    int             count_h;
	int				**map;
	char			*line;

	line = NULL;
    count_h = 0;
	fd = open("maps/testmap.cub", O_RDONLY);
	line = NULL;
	if (!(map = malloc(sizeof(int *) * cub->state.height)))
		return ;
	while (get_next_line(fd, &line))
	{
		if (lineIsMap(line)) 
		{		
			map[count_h] = strto_intp(line, count_h, cub);
			count_h++;
		}
	}
	if (lineIsMap(line)) 	
		map[count_h] = strto_intp(line, count_h, cub);
	close(fd);
	cub->game.worldMap = map;
}