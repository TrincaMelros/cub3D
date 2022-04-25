/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 13:22:31 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_player(t_cub3d *cub)
{
	load_wall_floor(cub);
	load_player(cub);

}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == MOVE_UP)
		cub->keys.up = 1;
	else if (keycode == MOVE_DOWN)
		cub->keys.down = 1;
	else if (keycode == MOVE_LEFT)
		cub->keys.left = 1;
	else if (keycode == MOVE_RIGHT)
		cub->keys.right = 1;
	else if (keycode == ESC)
		free_and_quit();
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == MOVE_UP)
		cub->keys.up = 0;
	else if (keycode == MOVE_DOWN)
		cub->keys.down = 0;
	else if (keycode == MOVE_LEFT)
		cub->keys.left = 0;
	else if (keycode == MOVE_RIGHT)
		cub->keys.right = 0;
	else if (keycode == ESC)
		free_and_quit();
	return (0);
}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == MOVE_UP)
		cub->keys.up = true;
	else if (keycode == MOVE_DOWN)
		cub->keys.down = true;
	else if (keycode == MOVE_LEFT)
		cub->keys.left = true;
	else if (keycode == MOVE_RIGHT)
		cub->keys.right = true;
	else if (keycode == ESC)y
		free_and_quit();
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == MOVE_UP)
		cub->keys.up = false;
	else if (keycode == MOVE_DOWN)
		cub->keys.down = false;
	else if (keycode == MOVE_LEFT)
		cub->keys.left = false;
	else if (keycode == MOVE_RIGHT)
		cub->keys.right = false;
	else if (keycode == ESC)
		free_and_quit();
	return (0);
}
