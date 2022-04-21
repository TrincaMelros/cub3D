/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:31:14 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/18 11:45:25 by fbarros          ###   ########.fr       */
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

void	error_exit(char *s)
{
	exit(ft_error(s));
}

void	free_and_exit(char *s)
{
	t_cub3d	*cub3d;
	
	cub3d = get_data(NULL);
	free_all(cub3d);
	error_exit(s);
}

void	free_and_quit(void)
{
	t_cub3d *cub3d;

	cub3d = get_data(NULL);
	free_all(cub3d);
	exit (0);
}
