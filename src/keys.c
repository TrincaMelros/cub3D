/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:31:18 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:31:38 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (keycode == TURN_LEFT)
		cub->keys.turn_left = true;
	else if (keycode == TURN_RIGHT)
		cub->keys.turn_right = true;
	else if (keycode == ESC)
		free_n_quit();
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
	else if (keycode == TURN_LEFT)
		cub->keys.turn_left = false;
	else if (keycode == TURN_RIGHT)
		cub->keys.turn_right = false;
	else if (keycode == ESC)
		free_n_quit();
	return (0);
}

int	free_n_quit(void)
{
	t_cub3d	*cub3d;

	cub3d = get_data(NULL);
	free_all(cub3d);
	exit (0);
	return (0);
}
