/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:38:38 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 19:08:07 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	get_minimap_color(t_blocks block)
{
	if (block == WALL)
		return (MINIMAP_WALL);
	if (block == SPACE)
		return (MINIMAP_SPACE);
	return (TRANSPARENT);
}

static void	draw_player(const int step, t_cub3d *cub3d)
{
	const int	posx = (int)(cub3d->input.map.player.x * step - step / 4);
	const int	posy = (int)(cub3d->input.map.player.y * step - step / 4);

	draw_rect((t_point){.x = posx, .y = posy},
		(t_point){.x = step / 2 , .y = step / 2},
			MINIMAP_PLAYER, &cub3d->layers.minimap);
	// draw_player_vector(cub3d, step, posx, posy);
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

void	build_minimap(t_cub3d *cub3d)
{
<<<<<<< HEAD
	printf("player x is %f, player y is %f\n", cub->player.posX, cub->player.posY);
	mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window, cub->assets.player, cub->player.posX * 64, cub->player.posY * 64);
}
=======
	const int	width_step = MINIMAP_W / cub3d->input.map.w;
	const int	height_step = MINIMAP_H / cub3d->input.map.h;
	int			fixed_step;	
>>>>>>> origin/barros

	build_image(cub3d->mlx, &cub3d->layers.minimap, MINIMAP_W, MINIMAP_H);
	fixed_step = width_step;
	if (width_step > height_step)
		fixed_step = height_step;
	draw_minimap(cub3d, fixed_step);
	draw_player(fixed_step, cub3d);
}