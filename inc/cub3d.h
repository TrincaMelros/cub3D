/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:49:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/10 12:49:57 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# include "libft.h"

# define BUFFER_SIZE 1

typedef struct s_input {
	char	**txt;
	int		height;

	char	*north;
	char	*south;
	char	*west;
	char	*east;

	char	*floor_RGB;
	int		floor_R;
	int		floor_G;
	int		floor_B;
	int		floor_TRGB;

	char	*ceiling_RGB;
	int		ceiling_R;
	int		ceiling_G;
	int		ceiling_B;
	int		ceiling_TRGB;

	char	**map;
}		t_input;

// Refer to so_long for struct making

typedef struct s_cub3d
{
	t_input	input;
}		t_cub3d;

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
int		map_parsing(char *filename, t_input *input);

		/*  Mlx utils  */
int		create_trgb(int t, int r, int g, int b);
void	ft_pixel_put(int *addr, int x, int y, int color);

		/*	Other utils	*/
void	ft_puttxt(char **txt);

#endif
