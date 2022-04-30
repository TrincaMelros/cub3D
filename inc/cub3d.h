/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/30 13:37:27 by fbarros          ###   ########.fr       */
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
# include "keys.h"

# define BUFFER_SIZE 1

# define ROTSPEED 0.05
# define MOVESPEED 0.05

# define SUCCESS 0
# define SYSCALL 1
# define OTHER 2

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
	char	dir;
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

typedef	struct s_textures {
	int		*north;
	int		*south;
	int		*west;
	int		*east;
}	t_textures;

	/*	General Struct	*/
typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_input		input;
	t_player	player;
	t_images	imgs;
	t_img		img;
	t_layer		layers;
	t_keys		keys;
	t_textures	textures;
	int			map_buff[HEIGHT][WIDTH];
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
int		main_loop(t_cub3d *cub);

		/*	.cub Parsing	*/
void	cub_parsing(char *filename, t_input *input);

		/* Drawing Utils */
void	draw_rect(t_point coord, const t_point size, int color, t_img *img);
void	img_draw_verline(t_img *img, t_point p, const int y2, int color);
void	img_draw_horline(t_img *img, t_point p, const int x2, int color);

		/* Error Handling */
int		ft_error(char *s);
void	error_exit(char *s);
void	free_error_exit(char *s);

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/* Keys / Events */
int		key_press(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
int		free_n_quit(void);

		/*	Map Parsing	*/
t_map	map_validation(char **map);

		/* Memory Management */
void	*calloc_check(size_t nmemb, size_t size);
void	*set_free(void **ptr);
void	**twod_free(void **ptr_arr, size_t l_lenght);
void	**twod_realloc(void **ptr, size_t size);
t_cub3d	*get_data(t_cub3d *original);

		/* Minimap */
void	build_minimap(t_cub3d *cub3d);

		/*  Mlx utils  */
void	build_image(void *mlx_ptr, t_img *img, int width, int height);
int		create_trgb(int t, int r, int g, int b);
void	img_put_pixel(t_img *img, int color, int y, int x);

		/* Movements */
void	movement(t_cub3d *cub);

		/* Parsing utils */
int		all_assigned(t_input *input);
void	assign_texture(char **ptr, char *path);

		/* Raycasting Calcs */
void	initial_calcs(t_rc *rc, t_cub3d *cub, int x);
void	calc_sidedist(t_rc *rc, t_cub3d *cub);
void	dda_algo(t_rc *rc, t_cub3d *cub);
void	wall_calcs(t_rc *rc, t_cub3d *cub);

		/* Raycasting */
void	draw_lines(t_cub3d *cub);
void	raycaster(t_cub3d *cub);

		/* Textures */
void	load_image(t_cub3d *cub, int *texture, char *path, t_img *img);
void	load_texture(t_cub3d *cub);

		/* Setup */
void	set_game(t_cub3d *cub3d);



#endif
