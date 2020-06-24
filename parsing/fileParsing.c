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

int checkTextures(t_cub *cub, char *str){ 
	(void) cub;
	(void) str;
	return (1);
}

int checkColors(t_cub *cub, char *str) {
	(void) cub;
	(void) str;
	return (1);
}

int checkResolution(t_cub *cub, char *str) {
	int width;
	int height;
	int index = 0;
	
	str++;
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	printf("%s\n", str);
	width = nextNumber(str, &index);
	printf("index = %d\n", index);
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
	|| (*str == 'E' && *(str + 1) == 'A') || (*(str) == 'W' && *(str + 1) == 'E') || *str == 'S')
		return (checkTextures(cub, str));
	else if (*str == 'F' || *str == 'C')
		return (checkColors(cub, str));
	else if (*str == '0' || *str == '1')
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
		if (!lineIsUseless(line)) {
			cub->state.height++;
			if ((len = ft_strlen(line)) > cub->state.width)
				cub->state.width = len;
		}
		else
			return (checkFileElement(cub, line));
		free(line);
	}
	if (!lineIsUseless(line)) {
		cub->state.height++;
		if ((len = ft_strlen(line)) > cub->state.width)
			cub->state.width = len;
	}
	free(line);
	close(fd);
    getMap(cub);
	return (1);
}