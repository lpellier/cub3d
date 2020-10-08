/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:02:37 by lpellier          #+#    #+#             */
/*   Updated: 2020/10/08 19:02:38 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

/* TO DO LIST
// - Si la taille de fenêtre demandée dans la map est plus grande que celle de l’écran,
//   la taille de fenêtre doit être celle de l’écran. --> done for mms lib, still need opengl version
// - map path in first arg --> done
// - error handling for map --> done
// - if error, program must return(?) "Error\n" followed by another explication --> done */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>

# define RESX_MAX_MAC 3072
# define RESY_MAX_MAC 1920

# define WHITE 16777215
# define RED 16711680
# define GREEN 65280
# define BLUE 255

# define BUFFER_SIZE 32
# define FPS 60
# define MOV 0.15
# define ROT 0.1

# define ENNEMYMOV 0.1

# define LEFT_CLICK 	1
# define RIGHT_CLICK 	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125

# define KEY_TAB	48
# define KEY_MAJ	257
# define KEY_ESC	53
# define KEY_TAB	48

typedef struct		s_img
{
	void			   		  *img_ptr;
	unsigned int		*data;
	int							size_l;
	int							bpp;
	int							endian;
	int							height;
	int							width;
	char					  *path;
}							t_img;

typedef struct	s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	double			  time_taken;
	t_img 				img;
}						t_data;

typedef struct	s_game
{
	int 		**world_map; // [-Y][X]
	int			keys[66000];
}		t_game;

typedef struct	s_state
{
	double 			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double 			plane_y;


	int			height;
	int			width;

	double			time;
	double			old_time;
}		t_state;

typedef struct s_sprite
{
	double pos_x;
	double pos_y;
	t_img *texture;
} t_sprite;

typedef struct s_sprt
{
	double dist;
	int order;
} t_sprt;

typedef struct s_ray
{	
	// ray casting
	double camera_x;
	double raydir_x;
	double raydir_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	double wall_x;
	double step;
	double tex_pos;

	int map_x;
	int map_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int tex_num;
	int line_height;
	int draw_start;
	int draw_end;
	int j;
	int tex_x;
	int tex_y;

	//sprite casting
	double sprite_x;
	double sprite_y;
	double inv_det;
	double transform_x;
	double transform_y;

	int sprite_screen_x;
	int sprite_height;
	int draw_start_y;
	int draw_end_y;
	int sprite_width;
	int draw_start_x;
	int draw_end_x;
	int stripe;
	int tex_sprite_x;
	int y;
	int d;
	int tex_sprite_y;
	int color;
} t_ray;

typedef struct s_cub
{
	t_data data;
	t_ray ray;
	t_game game;
	t_state state;
	t_img minimap;
	t_img texture[4];  /* 0 -> SO || 1 -> NO || 2 -> EA || 3 -> WE */

	t_img sprite[3]; /* sprites tex */
	t_sprite *sprites; /* actual sprites on map */
	t_sprt *sprt;
	double *z_buffer; /* 1d buffer for sprites */
	int num_sprites; /* number of actual objects (sprites) in the map */ 
	int	sprite_index; /* only used in map parsing */
	int *sprite_order; /* sort of sprites */
	double *sprite_distance;

	int error;
	int	resx;
	int resy;

	int floor_color;
	int ceil_color;
	int **buffer;

	clock_t t;
}	t_cub;

/* Init functions */

int init_buffer(t_cub *cub);
void init_state(t_cub *cub);
int get_texture(t_cub *cub, int index);
int get_sprite(t_cub *cub, int index);
int get_tex_sprite(t_cub *cub);

/* Engine functions */

void put_pixel(t_img *img, int x, int y, unsigned int color);
void raycasting(t_cub *cub);
void put_square(t_cub *cub, int x, int y, unsigned int color);

void draw_minimap(t_cub *cub);

void 	draw_buffer(t_cub *cub);

int		free_and_destroy(t_cub *cub);

/* Event functions */

int		framer(clock_t t, t_cub *cub);

void loop(t_cub *cub);

int				update(t_cub *cub);
int				release(int key_code, void *param);
int				events(int key_code, void *param);
int				exit_wdw(int event, void *param);

void		move_forward(t_cub *cub);
void		move_backwards(t_cub *cub);
void		strafe_left(t_cub *cub);
void		strafe_right(t_cub *cub);
void		rotate_left(t_cub *cub);
void		rotate_right(t_cub *cub);

/* Map Parsing functions */

int			next_number(char *str, int *index);
int			next_color(char *str, int *index);
int			check_textures(t_cub *cub, char *str);
int			check_sprite(t_cub *cub, char *str);
int			check_colors(t_cub *cub, char *str);
void sort_sprites(t_cub *cub);
void count_sprites(t_cub *cub, char *str);
int					line_is_map(char *str);
int 				file_parsing(t_cub *cub, char *map_path);
void 				get_pos(int x, int y, char orientation, t_state *state);
void		get_pos2(char orientation, t_state *state);
int			strto_intp2(char c, int cur, int height, t_cub *cub);
int					*strto_intp(char *str, int height, t_cub *cub);
int				get_map(t_cub *cub, char *map_path);

/* Utility functions */

int	put_error(char *str);
int			get_next_line(int fd, char **line);
int			check_n(char *stock);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s1);
char		*ft_itoa(int n);

#endif
