/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:20:38 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/21 18:34:30 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			put_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	return (0);
}

int			init_and_protecc(t_cub *cub, char *map_path, int saved)
{
	if (!file_parsing(cub, map_path) || !init_buffer(cub) || \
	(cub->data.mlx_ptr = mlx_init()) == NULL)
		return (0);
	if (cub->data.img.width > RESX_MAX_MAC)
		cub->data.img.width = RESX_MAX_MAC;
	if (cub->data.img.height > RESY_MAX_MAC)
		cub->data.img.height = RESY_MAX_MAC;
	if (!saved)
		if ((cub->data.win_ptr = mlx_new_window(cub->data.mlx_ptr, \
		cub->data.img.width, cub->data.img.height, "cub3d")) == NULL)
			return (0);
	if (!get_tex_sprite(cub))
		return (0);
	cub->data.img.img_ptr = mlx_new_image(cub->data.mlx_ptr, \
	cub->data.img.width, cub->data.img.height);
	cub->data.img.data = (unsigned int *)mlx_get_data_addr(cub->data.img.\
	img_ptr, &cub->data.img.bpp, &cub->data.img.size_l, &cub->data.img.endian);
	return (1);
}

void		write_bmp_img(t_cub *cub, int fd)
{
	int		x;
	int		y;

	y = cub->data.img.height;
	while (y != -1)
	{
		x = 0;
		while (x < cub->data.img.width)
		{
			write(fd, &cub->buffer[y][x], (cub->data.img.bpp / 8));
			x++;
		}
		y--;
	}
}

void		write_bmp_header(t_cub *cub, int fd)
{
	int				file_size;
	int				header_size;
	int				pixel_offset;
	short int		plane;
	int				none;
	short int		bitpp;

	file_size = 54 + cub->data.img.height * cub->data.img.size_l;
	none = 0;
	pixel_offset = 54;
	plane = 1;
	header_size = 40;
	bitpp = (short int)cub->data.img.bpp;
	write(fd, "BM", 2);
	write(fd, &file_size, sizeof(int));
	write(fd, &none, sizeof(int));
	write(fd, &pixel_offset, sizeof(int));
	write(fd, &header_size, sizeof(int));
	write(fd, &cub->data.img.width, sizeof(int));
	write(fd, &cub->data.img.height, sizeof(int));
	write(fd, &plane, sizeof(short int));
	write(fd, &bitpp, sizeof(short int));
	write(fd, &none, sizeof(int));
	write(fd, &none, sizeof(int));
	write(fd, &none, sizeof(int));
	write(fd, &none, sizeof(int));
	write(fd, &none, sizeof(int));
	write(fd, &none, sizeof(int));
}

int			bmp_file(t_cub *cub)
{
	int		fd;

	if ((fd = open("saved.bmp", O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC)) < 0)
	{
		put_error("Couldn't save image.");
		return (0);
	}
	raycasting(cub, 1);
	write_bmp_header(cub, fd);
	write_bmp_img(cub, fd);
	return (1);
}

int			main(int ac, char **av)
{
	t_cub		cub;
	char		*map_path;

	init_state(&cub);
	if ((ac != 2 && ac != 3) || (ac == 3 && !ft_strncmp(av[2], "--save", 7)))
	{
		put_error("arg error");
		exit(0);
	}
	map_path = ft_strdup(av[1]);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
	{
		if (!init_and_protecc(&cub, map_path, 1) || !bmp_file(&cub))
			exit(0);
	}
	else
	{
		if (!init_and_protecc(&cub, map_path, 0))
			exit(0);
		raycasting(&cub, 0);
		loop(&cub);
	}
	return (1);
}
