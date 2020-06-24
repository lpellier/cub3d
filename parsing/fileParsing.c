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
	while (*str == ' ')
		str++;
	printf("%s\n", str);
	width = nextNumber(str, &index);
	printf("index = %d\n", index);
	str += index;
	while (*str == ' ')
		str++;
	height = nextNumber(str, &index);
	cub->data.img.width = width;
	cub->data.img.height = height;
	printf("width = %d height  = %d\n", width, height);
	return (1);
}

int checkFileElement(t_cub *cub, char *str) {
	while (*str == ' ')
		str++;
	if (*str == 'R')
		return (checkResolution(cub, str));
	else if ((*str == 'N' && *(str + 1) == 'O') || (*(str) == 'S' && *(str + 1) == 'O') \
	|| (*str == 'E' && *(str + 1) == 'A') || (*(str) == 'W' && *(str + 1) == 'E') || *str == 'S')
		return (checkTextures(cub, str));
	else if (*str == 'F' || *str == 'C')
		return (checkColors(cub, str));
	else if (*str == '\n' || *str == '0' || *str == '1')
		return (1);
	else
		return (0);
}

int fileParsing(t_cub *cub) {
    int fd;
    int height;
    char *line;

    line = NULL;
    height = 1;
	fd = open("maps/testmap.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		// if (!checkFileElement(cub, line))
		// 	return 1;
		height++;
		free(line);
	}
	cub->state.height = height;
	free(line);
	close(fd);
    
    getMap(cub);
	return (1);
}