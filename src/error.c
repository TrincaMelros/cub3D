/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:31:14 by fbarros           #+#    #+#             */
/*   Updated: 2022/03/21 12:38:38 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int		ft_error(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(s, 2);
	return (1); // for now
}

// void	error_general(int errnum, char *str) // ........
// {
// 	ft_putendl_fd("Error", 2);
// 	if (str)
// 		ft_putendl_fd(str, 2);
// 	if (errnum == SYSCALL)
// 		perror(strerror(errno));
// 	else if (errnum == MAPVAL)
// 	{

// 	}
// 	exit(errnum);
// }

void	free_and_exit(t_cub3d *cub3d, char *s) /*function pointer as 2nd arg??*/
{
	twoD_free((void **)cub3d->input.txt);
	ft_error(s);
	// ...
}
