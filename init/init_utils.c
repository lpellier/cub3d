/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:05:53 by lpellier          #+#    #+#             */
/*   Updated: 2020/11/05 14:56:10 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_state2(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		cub->texture[i].path = NULL;
	i = -1;
	while (++i < 3)
		cub->sprite[i].img_ptr = NULL;
	cub->error = 0;
	cub->resx = 0;
	cub->resy = 0;
	cub->state.old_time = 0;
	cub->state.width = 0;
	cub->map_path = NULL;
	cub->state.height = 0;
	cub->num_sprites = 0;
	cub->sprite_index = 0;
	cub->num_diff_sprites = 0;
	cub->ray.draw_start = 0;
}
