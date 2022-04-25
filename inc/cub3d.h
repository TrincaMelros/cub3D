/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/18 17:08:22 by fbarros          ###   ########.fr       */
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

# include "libft.h"
# include "events.h"

// ifeq ($(shell uname), Darwin)
// 	# include "key_macos.h"
// else ifeq ($(shell uname), Linux)
// 	# include "key_linux.h"
// endif

# define BUFFER_SIZE 1
# define ESC		53
# define MOVE_UP	13
# define MOVE_DOWN	1
# define MOVE_RIGHT	2
# define MOVE_LEFT	0

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

typedef enum e_blocks {
	VOID,
	SPACE,
	WALL,
	PLAYER,
}	t_blocks;

typedef struct s_position {
	char	dir;
	float	x;
	float	y;
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

typedef struct s_keys {
	int		up;
	int		down;
	int		left;
	int		right;
}	t_keys;

	/*	MLX	*/
typedef struct s_mlx {
	void	*mlx;
	void	*window;
	// t_img	*imgs;
}	t_mlx;

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
	t_mlx		mlx_obj;
	t_input		input;
	t_assets	assets;
	t_player	player;
	t_images	imgs;
	t_img		img;
	t_keys		keys;
	t_rc		rc;
	int			map_buff[HEIGHT][WIDTH];
	int			**texture;
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
void	free_and_exit(char *s);
void	error_exit(char *s);
void	free_and_quit(void);

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
t_map	map_validation(char **map);

		/*	.cub Parsing	*/
void	cub_parsing(char *filename, t_input *input);

		/*  Mlx utils  */
int		create_trgb(int t, int r, int g, int b);
void	img_put_pixel(t_img *img, int color, int y, int x);
void	img_draw_verLine(t_img *img, int x, int y1, int y2, int color);
int		key_close(int keycode, t_cub3d *cub3d);


		/*	Other utils	*/
void	ft_putstr_err(char *s);
void	ft_puttxt(char **txt);
bool	line_empty(char *line);
void	init_vars(t_cub3d *cub);

		/* Memory Management */
void	**twod_realloc(void **ptr, size_t size);
void	**twod_free(void **ptr_arr);
void	*set_free(void **ptr);
t_cub3d	*get_data(t_cub3d *original);
void	*calloc_check(size_t nmemb, size_t size);

		/* Movements */
void	movement(t_cub3d *cub);
int		key_hook(int keycode, t_cub3d *cub);
void	redraw_player(t_cub3d *cub);
int		key_press(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);

		/* Textures */
void	load_image(t_cub3d *cub, int *texture, char *path, t_img *img);
void	load_texture(t_cub3d *cub);

		/* Minimap */
void	img_assignment(t_cub3d *cub);
void	load_wall_floor(t_cub3d *cub);
void	load_player(t_cub3d *cub);
void	minimap_launcher(t_cub3d *cub);

		/* Raycasting */
void	draw_lines(t_cub3d *cub);
void	raycaster(t_cub3d *cub);

#endif
