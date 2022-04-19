/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/19 12:32:42 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(void *params)
{
	// Calculate and throw images to window
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)params;
	// put screen to window
	mlx_put_image_to_window(cub3d->mlx_obj.mlx, cub3d->mlx_obj.window,
		cub3d->imgs.screen.ptr, 0, 0);
	// put minimap to window
	// mlx_put_image_to_window(cub3d->mlx_obj.mlx, cub3d->mlx_obj.window,
	// 	cub3d->imgs.minimap.ptr, 0, 0);
	
	return (0);
}