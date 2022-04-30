/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:21:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/30 13:52:05 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_player_ns(t_cub3d *cub)
{
	if (cub->input.map.player.dir == 'N')
	{
		cub->player.dirX = 0.0;
		cub->player.dirY = -1.0;
		cub->player.planeX = 0.66;
		cub->player.planeY = 0.0;	
	}
	if (cub->input.map.player.dir == 'S')
	{
		cub->player.dirX = 0.0;
		cub->player.dirY = 1.0;
		cub->player.planeX = -0.66;
		cub->player.planeY = 0.00;	
	}
}

void set_player_we(t_cub3d *cub)
{
	if (cub->input.map.player.dir == 'W')
	{
		cub->player.dirX = -1.0;
		cub->player.dirY = 0.0;
		cub->player.planeX = 0.00;
		cub->player.planeY = -0.66;	
	}
	if (cub->input.map.player.dir == 'E')
	{
		cub->player.dirX = 1.0;
		cub->player.dirY = 0.0;
		cub->player.planeX = 0.0;
		cub->player.planeY = 0.66;
	}
}

static void	init_vars(t_cub3d *cub)
{
	cub->player.posX = cub->input.map.player.x;
	cub->player.posY = cub->input.map.player.y;
	set_player_ns(cub);
	set_player_we(cub);
	cub->textures.north = (int *)calloc_check(1, sizeof(int) * \
	(TEXSIZE * TEXSIZE));
	cub->textures.south = (int *)calloc_check(1, sizeof(int) * \
	(TEXSIZE * TEXSIZE));
	cub->textures.east = (int *)calloc_check(1, sizeof(int) * \
	(TEXSIZE * TEXSIZE));
	cub->textures.west = (int *)calloc_check(1, sizeof(int) * \
	(TEXSIZE * TEXSIZE));
}

void	set_game(t_cub3d *cub3d)
{
	init_vars(cub3d);
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");

}

int	main_loop(t_cub3d *cub)
{
	movement(cub);
	raycaster(cub);
	draw_lines(cub);
	return (0);
}
