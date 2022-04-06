/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:34:50 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/06 15:30:55 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*set_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL); // ??
}

void	**twod_free(void **ptr_arr)
{
	void	**ptr;
	
	ptr = ptr_arr;
	if (ptr && *ptr)
	{
		while (*ptr)
		{
			free(*ptr);
			*ptr++ = NULL;
		}
		free(*ptr);
		free(ptr_arr);
		ptr = NULL;
	}
	return (NULL);
}

void	**twod_realloc(void **ptr, const size_t size)
/**
 * allocates size pointers set to NULL and "adds" to pointer
 * if no size returns pointer
*/
{
	void 	**tmp;
	int		i;

	i = -1;
	tmp = ptr;
	if(!size)
		return (ptr); // ?? not sure
	while(tmp[++i])
		continue ;
	ptr = ft_calloc(i + size + 1, sizeof(*ptr));
	if (!ptr)
		return (NULL);
	i = -1;
	while (tmp[++i])
		ptr[i] = tmp[i]; // or memccpy for each string ??
	free(tmp);
	return (ptr);
}

t_cub3d *get_data(t_cub3d *original)
{
	static t_cub3d *data;
	
	if (original != NULL) {
		data = original;
	}
	return (data);
}