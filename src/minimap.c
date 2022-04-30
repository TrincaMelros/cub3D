/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:38:38 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/26 13:37:41 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	const t_point	pos = (t_point){.x = (int)(cub3d->input.map.player.x
			* step - step / 4),
		.y = (int)(cub3d->input.map.player.y * step - step / 4)};

	draw_rect(pos, (t_point){.x = step / 2, .y = step / 2},
		MINIMAP_PLAYER, &cub3d->layers.minimap);
}

static void	draw_minimap(t_cub3d *cub3d, int step)
{
	int	x;
	int	h;

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
	const int	width_step = MINIMAP_W / cub3d->input.map.w;
	const int	height_step = MINIMAP_H / cub3d->input.map.h;
	int			fixed_step;

	build_image(cub3d->mlx, &cub3d->layers.minimap, MINIMAP_W, MINIMAP_H);
	fixed_step = width_step;
	if (width_step > height_step)
		fixed_step = height_step;
	draw_minimap(cub3d, fixed_step);
	draw_player(fixed_step, cub3d);
}