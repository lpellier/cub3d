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

# define BUFFER_SIZE 32
# define FPS 60
# define MOV 0.15
# define ROT 0.1

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
	void			*img_ptr;
	unsigned int	*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				height;
	int				width;
	char			*path;
}					t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	time_taken;
	t_img 	img;
}		t_data;

typedef struct	s_game
{
	int 		**worldMap;
	int			keys[66000];
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

typedef struct s_sprite
{
	double posX;
	double posY;
	t_img *texture;
} t_sprite;

typedef struct s_sprt
{
	double dist;
	int order;
} t_sprt;

typedef struct s_cub
{
	t_data data;
	t_game game;
	t_state state;
	t_img minimap;
	t_img texture[4];  // 0 -> SO || 1 -> NO || 2 -> EA || 3 -> WE

	t_img sprite[3]; // sprites tex
	t_sprite *sprites; // actual sprites on map
	t_sprt *sprt;
	double *zBuffer; // 1d buffer for sprites
	int numSprites; // number of actual objects (sprites) in the map 
	int	spriteIndex; // only used in map parsing
	int *spriteOrder; // sort of sprites
	double *spriteDistance;

	int floorColor;
	int ceilColor;
	int **buffer;

	clock_t t;
}	t_cub;

// Init functions

int initBuffer(t_cub *cub);
void initState(t_cub *cub);
int getTexture(t_cub *cub, int index);
int getSprite(t_cub *cub, int index);
int getTexSprite(t_cub *cub);

// Engine functions

void putPixel(t_img *img, int x, int y, unsigned int color);
void raycasting(t_cub *cub);
void putSquare(t_img *img, int x, int y, int width, int height, unsigned int color);

// void drawMinimap(t_cub *cub);

void 	drawBuffer(t_cub *cub);

int		freeAndDestroy(t_cub *cub);

// Event functions

int		framer(clock_t t, t_cub *cub);

void loop(t_cub *cub);

int				update(t_cub *cub);
int				release(int keyCode, void *param);
int				events(int keyCode, void *param);
int				exitWdw(int event, void *param);

void		moveForward(t_cub *cub);
void		moveBackwards(t_cub *cub);
void		strafeLeft(t_cub *cub);
void		strafeRight(t_cub *cub);
void		rotateLeft(t_cub *cub);
void		rotateRight(t_cub *cub);

// Map Parsing functions

void sortSprites(t_cub *cub);
void countSprites(t_cub *cub, char *str);
int					lineIsMap(char *str);
int 				fileParsing(t_cub *cub);
void 				getPos(int x, int y, char orientation, t_state *state);
int					*strto_intp(char *str, int height, t_cub *cub);
void				getMap(t_cub *cub);

// Utility functions

int			get_next_line(int fd, char **line);
int			check_n(char *stock);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s1);
// static char	*ft_strrev(char *str);
char		*ft_itoa(int n);

#endif