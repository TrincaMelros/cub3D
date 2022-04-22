/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/18 11:50:24 by fbarros          ###   ########.fr       */
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

void	move(t_cub3d *cub, int movement)
{
	if (movement == UP)
	{
	    if(cub->input.map.top_left[(int)(cub->player.posX + cub->player.dirX * \
		MOVESPEED)][(int)(cub->player.posY)] == SPACE)
			cub->player.posX += cub->player.dirX * MOVESPEED;
    	if(cub->input.map.top_left[(int)(cub->player.posX)][(int)\
		(cub->player.posY + cub->player.dirY * MOVESPEED)] == SPACE)
			cub->player.posY += cub->player.dirY * MOVESPEED;	
	}
	if (movement == DOWN)
	{
		if(cub->input.map.top_left[(int)(cub->player.posX - cub->player.dirX * \
		MOVESPEED)][(int)(cub->player.posY)] == SPACE)
			cub->player.posX -= cub->player.dirX * MOVESPEED;
    	if(cub->input.map.top_left[(int)(cub->player.posX)][(int)\
		(cub->player.posY - cub->player.dirY * MOVESPEED)] == SPACE)
			cub->player.posY -= cub->player.dirY * MOVESPEED;	
	}
}

void	rotate(t_cub3d *cub, int rotate)
{
	double olddirx;
	
	olddirx = 0;
	if (rotate == RIGHT)
	{
		olddirx = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(cub->player.rotspeed) - cub->player.dirY * sin(cub->player.rotspeed);
		cub->player.dirY = olddirx * sin(cub->player.rotspeed) + cub->player.dirY * cos(cub->player.rotspeed);	
	}
	if (rotate == LEFT)
	{
		olddirx = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(-cub->player.rotspeed) - cub->player.dirY * sin(-cub->player.rotspeed);
		cub->player.dirY = olddirx * sin(-cub->player.rotspeed) + cub->player.dirY * cos(-cub->player.rotspeed);
	}
}

void	movement(t_cub3d *cub)
{
	if (cub->keys.up)
		move(cub, UP);
	if (cub->keys.down)
		move(cub, DOWN);
	if (cub->keys.left)
		rotate(cub, LEFT);
	if (cub->keys.right)
		rotate(cub, RIGHT);
}
