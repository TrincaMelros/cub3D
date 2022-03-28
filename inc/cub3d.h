/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/28 14:36:19 by fbarros          ###   ########.fr       */
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

# include "libft.h"
# include "events.h"
# include "ft_error.h"

# define BUFFER_SIZE 1

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_color {
	int	R;
	int	G;
	int	B;
	int	TRGB;
}	t_color;

	/*	Parsing Struct	*/
typedef struct s_input {
	char	**txt;
	char	*north;
	char	*south;
	char	*west;
	char	*east;

	t_color floor;
	t_color	ceiling;

	char	**map;
	int		map_w;
	int		map_h;
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

	/*	MLX	*/
typedef struct s_mlx {
	void	*mlx;
	void	*window;
	// int		width;
	// int		height;
	t_img	*imgs;
}	t_mlx;


	/*	General Struct	*/
typedef struct s_cub3d
{
	t_input	input;
	t_mlx	mlx_obj;
	t_img	*imgs; // or imgs[7] (raycasting including floor and ceiling, no, so, ea, we, sprites)
}		t_cub3d;

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
int		map_parsing(char *filename, t_input *input);

		/*  Mlx utils  */
int		create_trgb(int t, int r, int g, int b);
void	ft_pixel_put(int *addr, int x, int y, int color);

		/*	Other utils	*/
void	ft_putstr_err(char *s);
void	ft_puttxt(char **txt);
int		twoD_free(void **ptr_arr);
void	**twoD_realloc(void **ptr, size_t size);

#endif
