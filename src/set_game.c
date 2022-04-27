/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:21:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:49:48 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	floor_ceiling(void *mlx_ptr, t_img *screen, const t_input input)
// {
// 	t_point	p;

// 	p.y = -1;
// 	p.x = 0;
// 	build_image(mlx_ptr, screen, WIDTH, HEIGHT);
// 	while (++p.y <= HEIGHT / 2)
// 		img_draw_horline(screen, p, WIDTH, input.ceiling.trgb);
// 	while (p.y < HEIGHT)
// 	{
// 		img_draw_horline(screen, p, WIDTH, input.floor.trgb);
// 		p.y++;
// 	}
//}

void	set_game(t_cub3d *cub3d)
{
	// init mlx and window
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	// build screen img and paint wall/ceiling
	// floor_ceiling(cub3d->mlx, &cub3d->layers.screen, cub3d->input);
	//	build_minimap(cub3d);
	// mlx_hook(cub3d.window, X_EVENT_KEY_PRESS, 0, &key_press, &cub3d); // kinda copied from l-yohai
}
