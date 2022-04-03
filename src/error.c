/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:31:14 by fbarros           #+#    #+#             */
/*   Updated: 2022/03/30 12:05:06 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_error(char *s)
{
	ft_putendl_fd("Error", 2);
	if (!s)
	{
		perror(strerror(errno));
		return(SYSCALL);
	}
	ft_putendl_fd(s, 2);
	return(OTHER);
}

void	error_exit(char *s) // exit numcode as 2nd param??
{
	exit(ft_error(s));
}

void	free_and_exit(t_cub3d *cub3d, char *s)
{
	twod_free((void **)cub3d->input.txt);
	error_exit(s);
}
