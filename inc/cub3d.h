/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/21 14:38:44 by fbarros          ###   ########.fr       */
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
# include <errno.h>
# include <string.h>
# include <stdbool.h>

# include "libft.h"
# include "events.h"

# define BUFFER_SIZE 1

	/*	Error ID	*/
# define SYSCALL 1
# define MAPVAL 2
# define OTHER 3

// typedef enum	e_error {
// 	SYSCALL,
// 	MAPVAL,
// 	OTHER
// }	t_error;

typedef struct s_color {
	int	R;	
	int	G;	
	int	B;
	int	TRGB;	
}	t_color;

	/*	Parsing Struct	*/
typedef struct s_input {
	char	**txt;
	int		height;

	char	*north;
	char	*south;
	char	*west;
	char	*east;

	t_color floor;
	t_color	ceiling;

	char	**map;
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
	int		width;
	int		height;
	t_img	*imgs;
}	t_mlx;


	/*	General Struct	*/
typedef struct s_cub3d
{
	t_mlx	mlx_obj;
	t_input	input;
	// t_error	errnum;
}		t_cub3d;

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
int		map_parsing(char *filename, t_input *input);

		/*  Mlx utils  */
int		create_trgb(int t, int r, int g, int b);
void	ft_pixel_put(int *addr, int x, int y, int color);

		/*	Error Handling	*/
void	error_general(int errnum, char *str);
int		ft_error(char *s);

		/*	Other utils	*/
void	ft_putstr_err(char *s);
void	ft_puttxt(char **txt);
void	twoD_free(void **ptr_arr);
void	**twoD_realloc(void **ptr, size_t size);

#endif
