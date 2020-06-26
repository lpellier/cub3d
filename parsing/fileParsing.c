#include "../cub3d.h"

int nextNumber(char *str, int *index) {
	int res = 0;
	int i = 0;

	while (str[i] >= '0'  && str[i] <= '9' && str[i]) {
		res = res * 10 + str[i] - 48;
		i++;
	}
	*index = i;
	return (res);
}

int nextColor(char *str, int *index) {
	int res = 0;
	int i = 0;

	while (str[i] == 32 || str[i] == 9 || str[i] == 10 \
	|| str[i] == 11 || str[i] == 12 || str[i] == 13)
		i++;
	if (str[i] == ',')
		i++;
	while (str[i] == 32 || str[i] == 9 || str[i] == 10 \
	|| str[i] == 11 || str[i] == 12 || str[i] == 13)
		i++;
	while (str[i] >= '0'  && str[i] <= '9' && str[i]) {
		res = res * 10 + str[i] - 48;
		i++;
	}
	*index = i;
	return (res);
}

int checkTextures(t_cub *cub, char *str){ 
	int index;
	
	index = 0;	
	if (*str == 'N')
		index = 1;
	else if (*str == 'E')
		index = 2;
	else if (*str == 'W')
		index = 3;
	str += 2;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (!(cub->texture[index].path = ft_strdup(str)))
		return (0);
	return (1);
}

int checkSprite(t_cub *cub, char *str) {
	str += 1;

	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (!(cub->sprite.path = ft_strdup(str)))
		return (0);
	return (1);
}

int checkColors(t_cub *cub, char *str) {
	int r;
	int g;
	int b;
	int index;
	int *rgb;

	if (*str == 'F')
		rgb = &cub->floorColor;
	else if (*str == 'C')
		rgb = &cub->ceilColor;
	else
	{
		printf("Color Error\n");
		return (0);
	}
	str++;
	r = nextColor(str, &index);
	str += index;
	g = nextColor(str, &index);
	str += index;
	b = nextColor(str, &index);

	*rgb = 65536 * r + 256 * g + b;
	if (*rgb >= 0 && *rgb <= 2147483647)
		return (1);
	else
		return 0;
}

int checkResolution(t_cub *cub, char *str) {
	int width;
	int height;
	int index = 0;
	
	str++;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	width = nextNumber(str, &index);
	str += index;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	height = nextNumber(str, &index);
	cub->data.img.width = width;
	cub->data.img.height = height;
	printf("WIN_width = %d WIN_height  = %d\n", width, height);
	return (1);
}

int checkFileElement(t_cub *cub, char *str) {
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == 'R')
		return (checkResolution(cub, str));
	else if ((*str == 'N' && *(str + 1) == 'O') || (*(str) == 'S' && *(str + 1) == 'O') \
	|| (*str == 'E' && *(str + 1) == 'A') || (*(str) == 'W' && *(str + 1) == 'E'))
		return (checkTextures(cub, str));
	else if (*str == 'S')
		return (checkSprite(cub, str));
	else if (*str == 'F' || *str == 'C')
		return (checkColors(cub, str));
	else if (*str == '0' || *str == '1' || !*str)
		return (1);
	else
		return (0);
}

int fileParsing(t_cub *cub) {
    int fd;
	int len;
    char *line;

    line = NULL;
	fd = open("maps/testmap.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (lineIsMap(line)) {
			cub->state.height++;
			if ((len = ft_strlen(line)) > cub->state.width)
				cub->state.width = len;
		}
		else
			if (!checkFileElement(cub, line))
				return (0);
		free(line);
	}
	if (lineIsMap(line)) {
		cub->state.height++;
		if ((len = ft_strlen(line)) > cub->state.width)
			cub->state.width = len;
	}
	free(line);
	close(fd);
    getMap(cub);
	return (1);
}