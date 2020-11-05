/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:27:52 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/05 17:28:10 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			check_file_element(t_cub *cub, char *str)
{
	while (*str == 32 || *str == 9 || *str == 10 \
	|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == 'R')
		return (check_resolution(cub, str));
	else if ((*str == 'N' && *(str + 1) == 'O') || (*(str) == 'S' && \
	*(str + 1) == 'O') || (*str == 'E' && *(str + 1) == 'A') || \
	(*(str) == 'W' && *(str + 1) == 'E'))
		return (check_textures(cub, str));
	else if (*str == 'S')
		return (check_sprite(cub, str));
	else if (*str == 'F' || *str == 'C')
		return (check_colors(cub, str));
	else if (*str == '1' || !*str)
		return (check_map_line(str));
	else
		return (-1);
}
