/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:15:00 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/29 12:55:07 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	all_assigned(t_input *input)
{
	if (input->north == NULL)
		return (0);
	if (input->south == NULL)
		return (0);
	if (input->west == NULL)
		return (0);
	if (input->east == NULL)
		return (0);
	if (input->floor.trgb == -1)
		return (0);
	if (input->ceiling.trgb == -1)
		return (0);
	return (1);
}

void	assign_texture(char **ptr, char *path)
{
	if (*ptr != NULL)
		free_error_exit(".cub: texture assigned two or more times.");
	else
		*ptr = path;
}

double	set_direction(char cardinal)
{
	/**
	 * if (cardinal == 'N')
	 * 		dirx = 0;
	 *		diry = -1;
	 * 		planex = 0.66;
	 * 		planey = 0;
	 * if (cardinal == 'S')
	 * 		dirx = 0;
	 *		diry = 1;
	 * 		planex = -0.66;	
	 * 		planey = 0;
	 * if (cardinal == 'E')
	 * 		dirx = 1;
	 *		diry = 0;
	 * 		planex = 0;	
	 * 		planey = -0.66;
	 * else
	 * 		dirx = -1;
	 *		diry = 0;
	 * 		planex = 0;
	 * 		planey = 0.66;
	 */
	if (cardinal == 'N')
		return (DEG90);
	if (cardinal == 'S')
		return (DEG270);
	if (cardinal == 'E')
		return (0);
	return (DEG180);
}
