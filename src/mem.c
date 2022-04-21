/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:34:50 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/21 21:25:24 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*calloc_check(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		free_error_exit(NULL);
	return (ptr);
}

void	*set_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	**twod_free(void **ptr_arr)
{
	void	**ptr;

	ptr = ptr_arr;
	if (ptr)
	{
		while (*ptr)
		{
			free(*ptr);
			*ptr++ = NULL;
		}
		if (*ptr)
			free(*ptr);
		free(ptr_arr);
		ptr = NULL;
	}
	return (NULL);
}

void	**twod_realloc(void **ptr, const size_t size)
/**
 * allocates size pointers set to NULL and "appends" to pointer
 * if no size returns pointer
*/
{
	void	**tmp;
	int		i;

	i = -1;
	tmp = ptr;
	if (!size)
		return (ptr);
	while (tmp[++i])
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

t_cub3d	*get_data(t_cub3d *original)
{
	static t_cub3d	*data;

	if (original != NULL)
		data = original;
	return (data);
}