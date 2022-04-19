/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:21:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/19 12:31:10 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	build_floor_ceiling(void *mlx_ptr, t_img *screen, const t_input input)
{
	int y;

	y = -1;
	build_image(mlx_ptr, screen, WIDTH, HEIGHT);
	while (++y <= HEIGHT / 2)
		img_draw_horLine(screen, y, 0, WIDTH, input.ceiling.trgb);
	while (y < HEIGHT)
		img_draw_horLine(screen, y++, 0, WIDTH, input.floor.trgb);
	
}

void	set_game(t_cub3d *cub3d)
{
	// init mlx and window
	cub3d->mlx_obj.mlx = mlx_init();
	cub3d->mlx_obj.window = mlx_new_window(cub3d->mlx_obj.mlx, WIDTH, HEIGHT, "Cub3D");
	
	// build images
	build_floor_ceiling(cub3d->mlx_obj.mlx, &cub3d->imgs.screen, cub3d->input);

	// mlx_put_image_to_window(cub3d.mlx_obj.mlx, cub3d.mlx_obj.mlx, cub3d.imgs.screen.ptr, 0, 0);

	// mlx_hook(cub3d.mlx_obj.window, X_EVENT_KEY_PRESS, 0, &key_press, &cub3d); // kinda copied from l-yohai
}