/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:15:00 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/04 18:02:16 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_err(char *s)
{
	if (write(1, s, ft_strlen(s)) == -1)
		exit(SYSCALL);
}

void	ft_puttext(char **text)
{
	while (*text)
	{
		ft_putstr_err(*text++);
		ft_putstr_err("\n");
	}
}
