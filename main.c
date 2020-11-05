/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:20:38 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/05 17:26:08 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			put_error(t_cub *cub, char *str)
{
	ft_printf("\033[31mError\n");
	ft_printf("%s\n\033[0m", str);
	cub->error = 1;
	return (0);
}

int			init_and_protecc(t_cub *cub, char *map_path, int saved)
{
	if ((cub->data.mlx_ptr = mlx_init()) == NULL || \
	!file_parsing(cub, map_path))
		return (0);
	mlx_get_screen_size(cub->data.mlx_ptr, &cub->rresx, &cub->rresy);
	if (cub->data.img.width > cub->rresx)
		cub->data.img.width = cub->rresx;
	if (cub->data.img.height > cub->rresy)
		cub->data.img.height = cub->rresy;
	if (!init_buffer(cub))
		return (0);
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

int			check_cub_extension(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 4] == '.' && str[i - 3] == 'c' && \
	str[i - 2] == 'u' && str[i - 1] == 'b')
		return (1);
	return (0);
}

void		init_everything(t_cub *cub, char *map_path, int saved)
{
	if (saved)
	{
		if (!init_and_protecc(cub, map_path, 1) || !bmp_file(cub))
		{
			free(map_path);
			exit(free_and_destroy(cub));
		}
	}
	else
	{
		if (!init_and_protecc(cub, map_path, 0))
		{
			free(map_path);
			exit(free_and_destroy(cub));
		}
	}
}

int			main(int ac, char **av)
{
	t_cub		cub;

	init_state(&cub);
	if ((ac != 2 && ac != 3) || (ac == 3 && !ft_strncmp(av[2], "--save", 7)))
		exit(put_error(&cub, "Arg error"));
	cub.map_path = ft_strdup(av[1]);
	if (!check_cub_extension(cub.map_path))
		exit(put_error(&cub, "File has to end with .cub"));
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		init_everything(&cub, cub.map_path, 1);
	else
	{
		init_everything(&cub, cub.map_path, 0);
		raycasting(&cub, 0);
		loop(&cub);
	}
	free(cub.map_path);
	return (1);
}
