/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:31:07 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(/* void *params */t_cub3d *cub3d)
{
	// raycast
	// mlx_put_image_to_window(cub3d->mlx, cub3d->window,
	// 	cub3d->layers.screen.ptr, 0, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window,
		cub3d->layers.minimap.ptr, 10, 10);
	return (SUCCESS);
}
