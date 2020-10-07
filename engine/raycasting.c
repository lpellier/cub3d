#include "../cub3d.h"

int cmp(const void *left, const void *right) {
	t_sprt *a = (t_sprt *)left;
	t_sprt *b = (t_sprt *)right;

	if (b->dist < a->dist)
		return (1);
	else if (a->dist < b->dist)
		return (-1);
	else
		return ((a->order < b->order) - (b->order < a->order));
}

void sort_sprites(t_cub *cub) {
	int i;

	i = -1;
	while (++i < cub->num_sprites) {
		cub->sprt[i].dist = cub->sprite_distance[i];
		cub->sprt[i].order = cub->sprite_order[i];	
	}
	qsort(cub->sprt, cub->num_sprites, sizeof(t_sprt), cmp);
	i = -1;
	while (++i < cub->num_sprites) {
		cub->sprite_distance[i] = cub->sprt[cub->num_sprites - i - 1].dist;
		cub->sprite_order[i] = cub->sprt[cub->num_sprites - i - 1].order;
	}
}

void sprite_casting(t_cub *cub) 
{
	int i;

	i = -1;
	while (++i < cub->num_sprites) {
		cub->sprite_order[i] = i;
		cub->sprite_distance[i] = ((cub->state.pos_x - cub->sprites[i].pos_x) * (cub->state.pos_x - cub->sprites[i].pos_x) \
		+ (cub->state.pos_y - cub->sprites[i].pos_y) * (cub->state.pos_y - cub->sprites[i].pos_y));
	}
	sort_sprites(cub);
	i = -1;
	// printf("player pos : x = %f, y = %f\n", cub->state.pos_x, cub->state.pos_y);
	while (++i < cub->num_sprites)
	{
		double sprite_x = cub->sprites[cub->sprite_order[i]].pos_x - cub->state.pos_x;
		double sprite_y = cub->sprites[cub->sprite_order[i]].pos_y - cub->state.pos_y;
		// printf("i = %d && order = %d\n", i, cub->sprite_order[i]);
		// printf("sprite_x = %f, sprite_y = %f\n", sprite_x, sprite_y);
		// printf("x = %f && y = %f\n\n", cub->sprites[cub->sprite_order[i]].pos_x, cub->sprites[cub->sprite_order[i]].pos_y);
		double inv_det = 1.0 / (cub->state.plane_x * cub->state.dir_y - cub->state.dir_x * cub->state.plane_y);

		double transform_x = inv_det * (cub->state.dir_y * sprite_x - cub->state.dir_x * sprite_y);
		double transform_y = inv_det * (-cub->state.plane_y * sprite_x + cub->state.plane_x * sprite_y);
		// printf("%f %f\n", transform_x, transform_y);
		int sprite_screen_x = (int)((cub->data.img.width / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(cub->data.img.height / (transform_y)));

		int draw_start_y = -sprite_height / 2 + cub->data.img.height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + cub->data.img.height / 2;
		if (draw_end_y >= cub->data.img.height)
			draw_end_y = cub->data.img.height - 1;
		
		int sprite_width = abs((int)(cub->data.img.height / (transform_y)));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= cub->data.img.width)
			draw_end_x = cub->data.img.width - 1;
		int stripe = draw_start_x - 1;
		while (++stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * cub->sprites[cub->sprite_order[i]].texture->width / sprite_width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < cub->data.img.width && transform_y < cub->z_buffer[stripe])
			{
				int y = draw_start_y - 1;
				while (++y < draw_end_y)
				{
					int d = (y) * 256 - cub->data.img.height * 128 + sprite_height * 128;
					int tex_y = ((d * cub->sprites[cub->sprite_order[i]].texture->height) / sprite_height) / 256;
					int color = cub->sprites[cub->sprite_order[i]].texture->data[cub->sprites[cub->sprite_order[i]].texture->width * tex_y + tex_x];
					if ((color & 0x00FFFFFF) != 0)
						cub->buffer[y][stripe] = color;
				}
			}
		}
	}
}

void raycasting(t_cub *cub)
{
	int x = -1;
    while (++x < cub->data.img.width)
	{
		double camera_x = 2 * x / (double)cub->data.img.width - 1;
		double raydir_x = cub->state.dir_x + cub->state.plane_x * camera_x;
		double raydir_y = cub->state.dir_y + cub->state.plane_y * camera_x;

		int map_x = (int)cub->state.pos_x;
		int map_y = (int)cub->state.pos_y;

		double side_dist_x;
		double side_dist_y;

		double delta_dist_x = (raydir_y == 0) ? 0 : ((raydir_x == 0) ? 1 : fabs(1 / raydir_x));
      	double delta_dist_y = (raydir_x == 0) ? 0 : ((raydir_y == 0) ? 1 : fabs(1 / raydir_y));
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = (cub->state.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - cub->state.pos_x) * delta_dist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = (cub->state.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - cub->state.pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (cub->game.world_map[map_x][map_y] == 1) 
				hit = 1;
		}

		int tex_num;

		if (side == 0) {
			perp_wall_dist = (map_x - cub->state.pos_x + (1 - step_x) / 2) / raydir_x;
			if (raydir_x > 0)
				tex_num = 0; // SOUTH
			else
				tex_num = 1; // NORTH
		}
		else {
			perp_wall_dist = (map_y - cub->state.pos_y + (1 - step_y) / 2) / raydir_y;
			if (raydir_y > 0)
				tex_num = 2; // EAST
			else
				tex_num = 3; // WEST
		}
		int line_height = (int)(cub->data.img.height / perp_wall_dist);

		int draw_start = -line_height / 2 + cub->data.img.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + cub->data.img.height / 2;
		if (draw_end >= cub->data.img.height)
			draw_end = cub->data.img.height - 1;

		unsigned int color;
		//texturing calculations

		//calculate value of wall_x
		double wall_x; //where exactly the wall was hit
		if (side == 0) wall_x = cub->state.pos_y + perp_wall_dist * raydir_y;
		else           wall_x = cub->state.pos_x + perp_wall_dist * raydir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int tex_x = (int)(wall_x * (double)(cub->texture[tex_num].width));
		if(side == 0 && raydir_x > 0) tex_x = cub->texture[tex_num].width - tex_x - 1;
		if(side == 1 && raydir_y < 0) tex_x = cub->texture[tex_num].width - tex_x - 1;
	
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * cub->texture[tex_num].height / line_height;
		// Starting texture coordinate
		double tex_pos = (draw_start - cub->data.img.height / 2 + line_height / 2) * step;
		for (int y = 0; y < draw_start; y++) 
		{
			color = cub->ceil_color;
			cub->buffer[y][x] = color;
		}
		for(int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int tex_y = (int)tex_pos & (cub->texture[tex_num].height - 1);
			tex_pos += step;
			color = cub->texture[tex_num].data[cub->texture[tex_num].height * tex_y + tex_x];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			if (perp_wall_dist > 5) color = (color >> 1) & 8355711;
			cub->buffer[y][x] = color;
		}
		for (int y = draw_end; y < cub->data.img.height; y++) 
		{
			color = cub->floor_color;
			cub->buffer[y][x] = color;
		}
		cub->z_buffer[x] = perp_wall_dist;
	}
	sprite_casting(cub);
	draw_minimap(cub);
	draw_buffer(cub);
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win_ptr, cub->data.img.img_ptr, 0, 0);
}
