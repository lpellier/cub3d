/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:17:49 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/21 18:43:51 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			exit_wdw(int event, void *param)
{
	t_cub		*cub;

	(void)event;
	cub = (t_cub *)param;
	exit (0);
}

void		loop(t_cub *cub)
{
	raycasting(cub, 0);
	mlx_hook(cub->data.win_ptr, 17, 1L << 17, exit_wdw, cub);
	mlx_hook(cub->data.win_ptr, 2, 1L << 0, events, cub);
	mlx_hook(cub->data.win_ptr, 3, 1L << 1, release, cub);
	mlx_loop_hook(cub->data.mlx_ptr, update, cub);
	mlx_loop(cub->data.mlx_ptr);
}
