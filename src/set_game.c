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

int	get_minimap_color(t_blocks block)
{
	if (block == WALL)
		return (MINIMAP_WALL);
	if (block == SPACE)
		return (MINIMAP_SPACE);
	return (TRANSPARENT);
}

static void	draw_player_vector(t_cub3d cub3d, int step, int posx, int posy)
{
	int	i;
	int	increment;


	i = -1;

	while (++i < VECTORSIZE)
	{
		// 
	}
}

static void	draw_player(const int step, t_cub3d *cub3d)
{
	const int	posx = (int)(cub3d->input.map.player.x * step - step / 4);
	const int	posy = (int)(cub3d->input.map.player.y * step - step / 4);

	draw_rect((t_point){.x = posx, .y = posy},
		(t_point){.x = step / 2 , .y = step / 2},
			MINIMAP_PLAYER, &cub3d->layers.minimap);
	draw_player_vector(cub3d, step, posx, posy);
}

static void	draw_minimap(t_cub3d *cub3d, int step)
{
	int 		x;
	int 		h;

	x = -1;
	while (++x < (int)cub3d->input.map.w)
	{
		h = -1;
		while (++h < (int)cub3d->input.map.h)
		{
			draw_rect((t_point){.x = x * step, .y = h * step},
				(t_point){.x = step - 1, .y = step - 1},
				get_minimap_color(cub3d->input.map.top_left[h][x]),
				&cub3d->layers.minimap);
		}
	}
}

static void	build_minimap(t_cub3d *cub3d)
{
	const int	width_step = MINIMAP_W / cub3d->input.map.w;
	const int	height_step = MINIMAP_H / cub3d->input.map.h;
	int			fixed_step;	

	fixed_step = width_step;
	if (width_step > height_step)
		fixed_step = height_step;
	draw_minimap(cub3d, fixed_step);
	draw_player(fixed_step, cub3d);
}

void	set_game(t_cub3d *cub3d)
{
	// init mlx and window
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");

	// build images
	build_floor_ceiling(cub3d->mlx, &cub3d->layers.screen, cub3d->input);

	build_image(cub3d->mlx, &cub3d->layers.minimap, MINIMAP_W, MINIMAP_H);
	build_minimap(cub3d);
	


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
