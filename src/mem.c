/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:34:50 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/29 12:14:32 by fbarros          ###   ########.fr       */
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

void	**twod_free(void **ptr_arr, size_t l_lenght)
{
	void	**ptr;

	ptr = ptr_arr;
	if (ptr)
	{
		while (*ptr || l_lenght)
		{
			free(*ptr);
			*ptr++ = NULL;
			if (l_lenght)
				l_lenght--;
		}
		if (*ptr)
			free(*ptr);
		free(ptr_arr);
		ptr = NULL;
	}
	return (NULL);
}

void	**twod_realloc(void **ptr, const size_t size)
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
