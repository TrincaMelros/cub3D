/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/25 19:07:50 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>

# include "libft.h"
# include "events.h"

// ifeq ($(shell uname), Darwin)
// 	# include "key_macos.h"
// else ifeq ($(shell uname), Linux)
// 	# include "key_linux.h"
// endif

# define BUFFER_SIZE 1

# define ROTSPEED 0.05
# define MOVESPEED 0.05

enum	e_error {
	SUCCESS,
	SYSCALL,
	OTHER
} ;

# define BUFFER_SIZE 1

# define WIDTH 640
# define HEIGHT 480
# define TEXSIZE 64

# define MINIMAP_W 432
# define MINIMAP_H 288
# define MINIMAP_WALL 0x88000088
# define MINIMAP_SPACE 0x88AAAAAA
# define MINIMAP_PLAYER 0x88880000
# define TRANSPARENT 0xFF000000

// in radians
# define DEG90 1.57079633
# define DEG180 3.14159265
# define DEG270 4.71238898
# define DEG360 6.28318531
# define VECTORSIZE 5

typedef enum e_blocks {
	VOID,
	SPACE,
	WALL,
	PLAYER,
}	t_blocks;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_position {
	double	dir;
	double	x;
	double	y;
}	t_position;

typedef struct s_map {
	t_blocks		**top_left;
	unsigned int	w;
	unsigned int	h;
	t_position		player;
}	t_map;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	trgb;
}	t_color;

	/*	Parsing Struct	*/
typedef struct s_input {
	char	**txt;
	char	*north;
	char	*south;
	char	*west;
	char	*east;

	t_color	floor;
	t_color	ceiling;

	t_map	map;
}		t_input;

	/*	Images	*/
//typedef struct s_img {
//	void	*ptr;
//	int		w;
//	int		h;
//	int		*addr;
//	int		bpp;
//	int		line;
//	int		endian;
//}	t_img;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_assets {
	void	*floor;
	void	*wall;
	void	*player;
	int		player_x;
	int		player_y;
}	t_assets;

typedef struct s_player {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_layer {
	t_img		screen;
	t_img		minimap;
	t_img		wall;
	t_img		player;
}	t_layer;

typedef struct s_keys {
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	turn_left;
	bool	turn_right;
}	t_keys;

typedef struct s_rc {
	double	camerax;
	double	raydirx;
	double	raydiry;
	
	int		mapx;
	int		mapy;

	double	sidedistx;
	double	sidedisty;

	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;

	int		stepx;
	int		stepy;

	int		hit;
	int		side;

	int		lineheight;
	int		drawstart;
	int		drawend;

	int		texnum;
	double	wallx;
	int		texx;

	double	step;
}	t_rc;

typedef struct s_images {
	t_img	screen;
	t_img	minimap;
	
}	t_images;

	/*	General Struct	*/
typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_input		input;
	t_assets	assets;
	t_player	player;
	t_images	imgs;
	t_img		img;
	t_layer		layers;
	t_keys		keys;
	t_rc		rc;
	int			map_buff[HEIGHT][WIDTH];
	int			*texture;
}		t_cub3d;

	/* RM */
# ifdef DEBUG_MODE
#  define DEBUG(x) x
#  include "test.h"
# else
#  define DEBUG(x)
# endif
	/* RM */

void	free_all(t_cub3d *cub3d);

		/* Error Handling */
int		ft_error(char *s);
void	error_exit(char *s);
void	free_error_exit(char *s);
void	free_and_quit(void);

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
t_map	map_validation(char **map);

		/*	.cub Parsing	*/
void	cub_parsing(char *filename, t_input *input);

		/* Parsing utils */
int		all_assigned(t_input *input);
void	assign_texture(char **ptr, char *path);
double	set_direction(char cardinal);

		/*  Mlx utils  */
void	build_image(void *mlx_ptr, t_img *img, int width, int height);
int		create_trgb(int t, int r, int g, int b);
void	img_put_pixel(t_img *img, int color, int y, int x);
int		key_close(int keycode, t_cub3d *cub3d);

		/* Drawing Utils */
void	img_draw_verline(t_img *img, t_point p, const int y2, int color);
void	img_draw_horline(t_img *img, t_point p, const int x2, int color);
void	draw_rect(t_point coord, const t_point size, int color, t_img *img);

		/* Memory Management */
void	**twod_realloc(void **ptr, size_t size);
void	**twod_free(void **ptr_arr);
void	*set_free(void **ptr);
t_cub3d	*get_data(t_cub3d *original);
void	*calloc_check(size_t nmemb, size_t size);

		/* Keys / Events */
int		key_hook(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
int		key_press(int keycode, t_cub3d *cub);

		/* Textures */
void	load_image(t_cub3d *cub, int *texture, char *path, t_img *img);
void	load_texture(t_cub3d *cub);
		/* Movements */
void	movement(t_cub3d *cub);

		/* Minimap */
void	build_minimap(t_cub3d *cub3d);

		/* Settup and Events (for now) */
void	set_game(t_cub3d *cub3d);
int		key_events(int keycode, t_cub3d *cub3d);
int		button_press(int button, int x, int y, t_cub3d *cub3d);

		/* Raycasting */
void	draw_lines(t_cub3d *cub);
void	raycaster(t_cub3d *cub);
int		main_loop(t_cub3d *cub3d);
// int		main_loop(void *params);

#endif
