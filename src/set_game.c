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

static void	set_player_ns(t_cub3d *cub)
{
	if (cub->input.map.player.dir == 'N')
	{
		cub->player.dirx = 0.0;
		cub->player.diry = -1.0;
		cub->player.planex = 0.66;
		cub->player.planey = 0.0;
	}
	if (cub->input.map.player.dir == 'S')
	{
		cub->player.dirx = 0.0;
		cub->player.diry = 1.0;
		cub->player.planex = -0.66;
		cub->player.planey = 0.00;
	}
}

static void	set_player_we(t_cub3d *cub)
{
	if (cub->input.map.player.dir == 'W')
	{
		cub->player.dirx = -1.0;
		cub->player.diry = 0.0;
		cub->player.planex = 0.00;
		cub->player.planey = -0.66;
	}
	if (cub->input.map.player.dir == 'E')
	{
		cub->player.dirx = 1.0;
		cub->player.diry = 0.0;
		cub->player.planex = 0.0;
		cub->player.planey = 0.66;
	}
}

static void	init_vars(t_cub3d *cub)
{
	cub->player.posx = cub->input.map.player.x;
	cub->player.posy = cub->input.map.player.y;
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
	build_image(cub3d->mlx, &cub3d->img, WIDTH, HEIGHT);
	load_texture(cub3d);
	mlx_loop_hook(cub3d->mlx, &main_loop, cub3d);
	mlx_hook(cub3d->window, X_BUTTON_EXIT, (1L << 17), &free_n_quit, cub3d);
	mlx_hook(cub3d->window, KEY_PRESS, 0, &key_press, cub3d);
	mlx_hook(cub3d->window, KEY_RELEASE, 0, &key_release, cub3d);
}
