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

void	ft_putstr_err(char *s)
{
	if (write(1, s, ft_strlen(s)) == -1)
		error_general(SYSCALL, 0);
}

void	ft_puttext(char **text)
{
	while (*text)
	{
		ft_putstr_err(*text++);
		ft_putstr_err("\n");
	}
}