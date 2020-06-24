#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 32

# define LEFT_CLICK 	1
# define RIGHT_CLICK 	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# define WIN_WIDTH 1920	
# define WIN_HEIGHT 1080

# define MOVE_SPEED 0.2
# define ROT_SPEED 0.1

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
	void			*img_ptr;
	unsigned int	*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img 	img;
}		t_data;

typedef struct	s_game
{
	int 		**worldMap;
	int			keys[6600];
}		t_game;

typedef struct	s_state
{
	double 			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double 			planeY;


	int			height;
	int			width;

	// variables for time.h
	double			time;
	double			oldTime;
}		t_state;

typedef struct s_cub
{
	t_data data;
	t_game game;
	t_state state;
	t_img minimap;
	t_img texture[4];
	unsigned int buffer[WIN_HEIGHT][WIN_WIDTH];

}	t_cub;

// Engine functions

void putPixel(t_img *img, int x, int y, unsigned int color);
void raycasting(t_cub *cub);
void putSquare(t_img *img, int x, int y, int width, int height, unsigned int color);

// void drawMinimap(t_cub *cub);

void drawBuffer(t_cub *cub);

int		freeAndDestroy(t_cub *cub);

// Event functions

int			update(t_cub *cub);
int				release(int keyCode, void *param);
int				events(int keyCode, void *param);
int			exitWdw(int event, void *param);

void		moveForward(t_cub *cub);
void		moveBackwards(t_cub *cub);
void		strafeLeft(t_cub *cub);
void		strafeRight(t_cub *cub);
void		rotateLeft(t_cub *cub);
void		rotateRight(t_cub *cub);

// Map Parsing functions

int		lineIsUseless(char *str);
int fileParsing(t_cub *cub);
void getPos(int x, int y, char orientation, t_state *state);
int				*strto_intp(char *str, int height, t_state *state);
void				getMap(t_cub *cub);

// Utility functions

int		get_next_line(int fd, char **line);
int			check_n(char *stock);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s1);

#endif