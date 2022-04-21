/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/21 23:47:57 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement(t_cub3d *cub, int new_x, int new_y)
{
	int x;
	int	y;

	x = (new_x + 1) / 64;
	y = (new_y + 1) / 64;

	printf("y is %d, x is %d", y, x);
	if (cub->input.map.top_left[y][x] == WALL)
		return;
	else
	{
		mlx_put_image_to_window(cub->mlx, cub->window, cub->assets.floor, cub->assets.player_x / 64, cub->assets.player_y / 64);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->assets.player, new_x, new_y);	
	}
	cub->assets.player_x = new_x;
	cub->assets.player_x = new_y;
}

int	key_hook(int keycode, t_cub3d *cub)
{
	printf("MOVEMENT\n");
	if (keycode == MOVE_UP)
		movement(cub, cub->assets.player_y - 2, cub->assets.player_x);
	if (keycode == MOVE_DOWN)
		movement(cub, cub->assets.player_y + 2, cub->assets.player_x);
	if (keycode == MOVE_LEFT)
		movement(cub, cub->assets.player_y, cub->assets.player_x - 2);
	if (keycode == MOVE_RIGHT)
		movement(cub, cub->assets.player_y, cub->assets.player_x + 2);
	return (0);
}
