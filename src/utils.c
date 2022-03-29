/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:15:00 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/29 11:09:44 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_err(char *s)
{
	if (write(1, s, ft_strlen(s)) == -1)
		exit(SYSCALL);
		// error_general(SYSCALL, 0);
}

void	ft_puttext(char **text)
{
	while (*text)
	{
		ft_putstr_err(*text++);
		ft_putstr_err("\n");
	}
}

void	twoD_free(void **ptr_arr)
{
	while (*ptr_arr)
	{
		free(*ptr_arr);
		*ptr_arr++ = NULL;
	}
}

void	**twoD_realloc(void **ptr, const size_t size)
/**
 * allocates size pointers set to NULL and "adds" to pointer
 * if no size returns pointer
*/
{
	void 	**tmp;
	int		i;

	tmp = ptr;
	i = -1;
	if(!size)
		return (ptr); // ?? not sure
	while(tmp[++i])
		continue ;
	ptr = ft_calloc(i + size + 1, sizeof(*ptr));
	if (!ptr)
		return (NULL);
	i = -1;
	while (tmp[++i])
		ptr[i] = tmp[i];
	free(tmp);
	return (ptr);
}
