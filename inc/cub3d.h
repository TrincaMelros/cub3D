/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/22 00:11:37 by fbarros          ###   ########.fr       */
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
# define MOVE_DOWN	3
# define MOVE_RIGHT	7
# define MOVE_LEFT	0

enum	e_error {
	SUCCESS,
	SYSCALL,
	OTHER
} ;

# define BUFFER_SIZE 1

# define WIDTH 1080
# define HEIGHT 720

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
typedef struct s_img {
	void	*ptr;
	int		w;
	int		h;
	int		*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_img;

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
}	t_keys;

	/*	General Struct	*/
typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_input		input;
	t_assets	assets;
	t_layer		layers;
	t_keys		keys;
}		t_cub3d;

	/* RM */
# ifdef DEBUG_MODE
#  define DEBUG(x) x
#  include "test.h"
# else
#  define DEBUG(x)
# endif
	/* RM */

void	free_all(t_cub3d *obj);

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

		/*  Mlx utils  */
void	build_image(void *mlx_ptr, t_img *img, int width, int height);
int		create_trgb(int t, int r, int g, int b);
void	img_put_pixel(t_img *img, int color, int y, int x);
void	img_draw_verline(t_img *img, int x, int y1, int y2, int color);
void	img_draw_horline(t_img *img, int y, int x1, int x2, int color);

		/* Drawing Utils */
void	draw_rect(t_point coord, const t_point size, int color, t_img *img);

		/*	Other utils	*/
void	ft_putstr_err(char *s);
void	ft_puttxt(char **txt);
bool	line_empty(char *line);

		/* Memory Management */
void	**twod_realloc(void **ptr, size_t size);
void	**twod_free(void **ptr_arr);
void	*set_free(void **ptr);
t_cub3d	*get_data(t_cub3d *original);
void	*calloc_check(size_t nmemb, size_t size);

		/* Movements */
void	movement(t_cub3d *cub, int new_x, int new_y);
int		key_hook(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
int		key_press(int keycode, t_cub3d *cub);

		/* Minimap */
void	img_assignment(t_cub3d *cub);
void	load_wall_floor(t_cub3d *cub);
void	load_player(t_cub3d *cub);

		/* Settup and Events (for now) */
void	set_game(t_cub3d *cub3d);
int		key_events(int keycode, t_cub3d *cub3d);
int		button_press(int button, int x, int y, t_cub3d *cub3d);

		/* Raycasting */
int		main_loop(t_cub3d *cub3d);
// int		main_loop(void *params);

#endif
