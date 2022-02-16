/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:15:00 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/10 17:15:01 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_putstr(char *s)
{
	if (write(1, s, ft_strlen(s)) == -1)
	{
		perror(strerror(errno));	// <----------- pass to error handling function
		exit(errno);
	}
}

void	ft_puttxt(char **txt)
{
	while (*txt)
	{
		ft_putstr(*txt++);
		ft_putstr("\n");
	}
}