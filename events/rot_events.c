/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:24:47 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/07 18:26:52 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		rotate_left(t_cub *cub)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = cub->state.dir_x;
	cub->state.dir_x = cub->state.dir_x * cos(ROT) - cub->state.dir_y * \
	sin(ROT);
	cub->state.dir_y = olddir_x * sin(ROT) + cub->state.dir_y * cos(ROT);
	oldplane_x = cub->state.plane_x;
	cub->state.plane_x = cub->state.plane_x * cos(ROT) - cub->state.plane_y * \
	sin(ROT);
	cub->state.plane_y = oldplane_x * sin(ROT) + cub->state.plane_y * \
	cos(ROT);
}

void		rotate_right(t_cub *cub)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = cub->state.dir_x;
	cub->state.dir_x = cub->state.dir_x * cos(-ROT) - cub->state.dir_y * \
	sin(-ROT);
	cub->state.dir_y = olddir_x * sin(-ROT) + cub->state.dir_y * cos(-ROT);
	oldplane_x = cub->state.plane_x;
	cub->state.plane_x = cub->state.plane_x * cos(-ROT) - cub->state.plane_y * \
	sin(-ROT);
	cub->state.plane_y = oldplane_x * sin(-ROT) + cub->state.plane_y * \
	cos(-ROT);
}
