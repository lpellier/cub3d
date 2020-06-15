#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include <time.h>
#include "libft/libft.h"

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

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	data_s
{
	void	*mlx_ptr;
	void	*win_ptr;
	// t_img 	img;
}		data_t;

typedef struct	game_s
{
	int 		**worldMap;
	int			mapHeight;
	int			mapWidth;
}		game_t;

typedef struct	state_s
{
	double 			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double 			planeY;
	// variables for time.h
	double			time;
	double			oldTime;
}		state_t;

typedef struct cub_s
{
	data_t data;
	game_t game;
	state_t state;
}	cub_t;

// Math functions

int				abs(int x);
int				min(int x, int y);
int				max(int x, int y);

// Engine functions

// void putVerticalLineToImage(data_t *data, int x, int drawStart, int drawEnd, int color);

void raycasting(data_t data, state_t *state, int **map, int width, int height);

void     drawVerticalLine(data_t data, int x0, int y0, int x1, int y1);
void    drawHorizontalLine(data_t data, int x0, int y0, int x1, int y1);
void        drawSquare(data_t data, int x, int y, int width, int height);

int				exit_hook(game_t *game);

#endif