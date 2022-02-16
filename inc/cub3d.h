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
	/**/
	int		floor_TRGB;
	/**/

	char	*ceiling_RGB;
	int		ceiling_R;
	int		ceiling_G;
	int		ceiling_B;
	/**/
	int		ceiling_TRGB;
	/**/

	char	**map;
}		t_input;

typedef struct s_cub3d
{
	t_input	input;
}		t_cub3d;

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Map Parsing	*/
int		map_parsing(char *filename, t_input *input);

/**********************************************************/
		/*  Mlx utils  */
int		create_trgb(int t, int r, int g, int b);
void	ft_pixel_put(int *addr, int x, int y, int color);
/**********************************************************/

		/*	Libft	*/
int		ft_strlen(char *str);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
int		ft_atoi(const char *nptr);
/**********************************************************/
void	ft_putstr(char *s);
void	ft_puttxt(char **txt);
/**********************************************************/

#endif
