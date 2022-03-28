/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:03:34 by fbarros           #+#    #+#             */
/*   Updated: 2022/03/28 14:07:28 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
#define FT_ERROR_H

# include "cub3d.h" // ...
# include <errno.h>

# define SYSCALL 1
# define OTHER 2
// # define MAPVAL 3

int		ft_error(char *s);
void	free_and_exit(t_cub3d *cub3d, char *s);
// void	error_general(int errnum, char *str);

#endif