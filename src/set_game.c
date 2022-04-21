/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:21:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/22 00:20:14 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	build_floor_ceiling(void *mlx_ptr, t_img *screen, const t_input input)
{
	int y;

	y = -1;
	build_image(mlx_ptr, screen, WIDTH, HEIGHT);
	while (++y <= HEIGHT / 2)
		img_draw_horline(screen, y, 0, WIDTH, input.ceiling.trgb);
	while (y < HEIGHT)
		img_draw_horline(screen, y++, 0, WIDTH, input.floor.trgb);
	
}

void	set_game(t_cub3d *cub3d)
{
	// init mlx and window
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	
	// build images
	build_floor_ceiling(cub3d->mlx, &cub3d->imgs.screen, cub3d->input);

	// mlx_put_image_to_window(cub3d.mlx, cub3d.mlx, cub3d.imgs.screen.ptr, 0, 0);

	// mlx_hook(cub3d.window, X_EVENT_KEY_PRESS, 0, &key_press, &cub3d); // kinda copied from l-yohai
}

int		key_events(int keycode, t_cub3d *cub3d)
{
	(void)cub3d;
	printf("key pressed: %d\n", keycode);
	
	if (keycode == ESC)
	{
		free_all(cub3d);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

int		button_press(int button, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	(void)cub3d;
	printf("button pressed: %d\n", button);
	return (SUCCESS);
}
