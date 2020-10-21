/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:02:37 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/21 18:17:27 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>

# define RESX_MAX_MAC	3072
# define RESY_MAX_MAC	1920

# define WHITE			16777215
# define RED			16711680
# define GREEN			65280
# define BLUE			255

# define BUFFER_SIZE	32
# define FPS			60
# define MOV			0.10
# define ROT			0.07

# define ENNEMYMOV		0.1

# if __APPLE__

#  define KEY_UP		126
#  define KEY_LEFT		123
#  define KEY_DOWN		125
#  define KEY_RIGHT		124
#  define KEY_W			13
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_ESC		53

# else

#  define KEY_UP		65362
#  define KEY_LEFT		65361
#  define KEY_DOWN		65364
#  define KEY_RIGHT		65363
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_ESC		65307

# endif

typedef	struct			s_img
{
	void			*img_ptr;
	unsigned int	*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				height;
	int				width;
	char			*path;
}						t_img;

typedef	struct			s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	double			time_taken;
	t_img			img;
}						t_data;

typedef	struct			s_game
{
	int				**world_map;
	char			keys[66000];
}						t_game;

typedef	struct			s_state
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	int				height;
	int				width;

	double			time;
	double			old_time;
}						t_state;

typedef	struct			s_sprite
{
	double			pos_x;
	double			pos_y;
	t_img			*texture;
}						t_sprite;

typedef	struct			s_sprt
{
	double			dist;
	int				order;
}						t_sprt;

typedef	struct			s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;

	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				tex_num;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				j;
	int				tex_x;
	int				tex_y;

	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;

	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_sprite_x;
	int				y;
	int				d;
	int				tex_sprite_y;
	int				color;
}						t_ray;

typedef	struct			s_cub
{
	t_data			data;
	t_ray			ray;
	t_game			game;
	t_state			state;
	t_img			minimap;
	t_img			texture[4];

	t_img			sprite[3];
	t_sprite		*sprites;
	t_sprt			*sprt;
	double			*z_buffer;
	int				num_sprites;
	int				sprite_index;
	int				*sprite_order;
	double			*sprite_distance;

	int				error;
	int				resx;
	int				resy;

	int				floor_color;
	int				ceil_color;
	int				**buffer;

	clock_t			t;
}						t_cub;

/*
** Init functions
*/

int						init_buffer(t_cub *cub);
int						get_texture(t_cub *cub, int index);
int						get_sprite(t_cub *cub, int index);
int						get_tex_sprite(t_cub *cub);

void					init_state(t_cub *cub);

/*
** Engine functions
*/

int						free_and_destroy(t_cub *cub);

void					put_pixel(t_img *img, int x, int y, unsigned int color);
void					raycasting(t_cub *cub, int saved);
void					raycasting2(t_cub *cub, int x);
void					raycasting3(t_cub *cub);
void					raycasting4(t_cub *cub);
void					raycasting5(t_cub *cub);
void					raycasting6(t_cub *cub);
void					raycasting7(t_cub *cub, int x);
void					sprite_casting(t_cub *cub);
void					sprite_casting2(t_cub *cub, int i);
void					sprite_casting3(t_cub *cub, int i);
void					sprite_casting4(t_cub *cub, int i);

void					put_square(t_cub *cub, int x, int y, \
						unsigned int color);
void					draw_minimap(t_cub *cub);
void					draw_buffer(t_cub *cub);

/*
** Event functions
*/

int						framer(clock_t t, t_cub *cub);
int						update(t_cub *cub);
int						release(int key_code, void *param);
int						events(int key_code, void *param);
int						exit_wdw(int event, void *param);

void					loop(t_cub *cub);
void					move_forward(t_cub *cub);
void					move_backwards(t_cub *cub);
void					strafe_left(t_cub *cub);
void					strafe_right(t_cub *cub);
void					rotate_left(t_cub *cub);
void					rotate_right(t_cub *cub);

/*
** Map Parsing functions
*/

int						next_number(char *str, int *index);
int						next_color(char *str, int *index);
int						check_textures(t_cub *cub, char *str);
int						check_sprite(t_cub *cub, char *str);
int						check_colors(t_cub *cub, char *str);
int						line_is_map(char *str);
int						file_parsing(t_cub *cub, char *map_path);
int						strto_intp2(char c, int cur, int height, t_cub *cub);
int						*strto_intp(char *str, int height, t_cub *cub);
int						get_map(t_cub *cub, char *map_path);
int						cmp(const void *left, const void *right);

void					sort_sprites(t_cub *cub);
void					sprite_sorting(t_cub *cub);
void					count_sprites(t_cub *cub, char *str);
void					get_pos(int x, int y, char orientation, t_state *state);
void					get_pos2(char orientation, t_state *state);

/*
** Utility functions
*/

int						init_and_protecc(t_cub *cub, char *map_path, int saved);
int						put_error(char *str);
int						get_next_line(int fd, char **line);
int						check_n(char *stock);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

char					*ft_strdup(const char *s1);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_substr(const char *s, unsigned int start, \
						size_t len);
char					*ft_itoa(int n);

size_t					ft_strlen(const char *s1);

#endif
