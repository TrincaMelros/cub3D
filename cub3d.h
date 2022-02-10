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
	char	**input;
	int		height;
}		t_input;

		/*	Get Next line */
int		get_next_line(char **line, int fd);

		/*	Libft	*/
int		ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif
