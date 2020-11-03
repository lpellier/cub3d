/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:20:38 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/03 15:39:46 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			put_error(char *str)
{
	ft_printf("\033[31mError\n");
	ft_printf("%s\n\033[0m", str);
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

int			free_and_ret(char *str)
{
	free(str);
	return (0);
}

int			main(int ac, char **av)
{
	t_cub		cub;
	char		*map_path;

	init_state(&cub);
	if ((ac != 2 && ac != 3) || (ac == 3 && !ft_strncmp(av[2], "--save", 7)))
		exit(put_error("Arg error"));
	map_path = ft_strdup(av[1]);
	if (!check_cub_extension(map_path))
		exit(put_error("File has to end with .cub"));
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
	{
		init_and_protecc(&cub, map_path, 1);
		bmp_file(&cub);
		exit(free_and_destroy(&cub, 1));
	}
	else
	{
		if (!init_and_protecc(&cub, map_path, 0))
			exit(free_and_destroy(&cub, 0));
		raycasting(&cub, 0);
		loop(&cub);
	}
	free(map_path);
	return (1);
}
