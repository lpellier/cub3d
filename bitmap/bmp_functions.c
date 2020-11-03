/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:22 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 18:24:21 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		write_bmp_img(t_cub *cub, int fd)
{
	int		x;
	int		y;

	y = cub->data.img.height - 1;
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
	cub->bmp.file_size = 54 + cub->data.img.height * cub->data.img.size_l;
	cub->bmp.none = 0;
	cub->bmp.pixel_offset = 54;
	cub->bmp.plane = 1;
	cub->bmp.header_size = 40;
	cub->bmp.bitpp = (short int)cub->data.img.bpp;
	write(fd, "BM", 2);
	write(fd, &cub->bmp.file_size, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.pixel_offset, sizeof(int));
	write(fd, &cub->bmp.header_size, sizeof(int));
	write(fd, &cub->data.img.width, sizeof(int));
	write(fd, &cub->data.img.height, sizeof(int));
	write(fd, &cub->bmp.plane, sizeof(short int));
	write(fd, &cub->bmp.bitpp, sizeof(short int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
	write(fd, &cub->bmp.none, sizeof(int));
}

int			bmp_file(t_cub *cub)
{
	int		fd;

	if ((fd = open("cub3d.bmp", O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC)) < 0)
	{
		put_error(cub, "Couldn't save image.");
		return (0);
	}
	raycasting(cub, 1);
	write_bmp_header(cub, fd);
	write_bmp_img(cub, fd);
	close(fd);
	free_and_destroy(cub);
	return (1);
}
