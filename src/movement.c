/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/30 13:53:31 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_cub3d *cub, int movement)
{
	if (movement == MOVE_UP)
	{
		if (cub->input.map.top_left[(int)(cub->player.posy)][(int)
		(cub->player.posx + cub->player.dirx * (MOVESPEED * 3))] == SPACE)
			cub->player.posx += cub->player.dirx * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posy + cub->player.diry
				* (MOVESPEED * 3))][(int)(cub->player.posx)] == SPACE)
			cub->player.posy += cub->player.diry * MOVESPEED;
	}
	if (movement == MOVE_DOWN)
	{
		if (cub->input.map.top_left[(int)(cub->player.posy)][(int)
		(cub->player.posx - cub->player.dirx * (MOVESPEED * 3))] == SPACE)
			cub->player.posx -= cub->player.dirx * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posy - cub->player.diry
				* (MOVESPEED * 3))][(int)(cub->player.posx)] == SPACE)
			cub->player.posy -= cub->player.diry * MOVESPEED;
	}
}

static void	strafe(t_cub3d *cub, int movement)
{
	if (movement == MOVE_RIGHT)
	{
		if (cub->input.map.top_left[(int)(cub->player.posy)][(int)
		(cub->player.posx - cub->player.diry * (MOVESPEED * 3))] == SPACE)
			cub->player.posx -= cub->player.diry * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posy + cub->player.dirx
				* (MOVESPEED * 3))][(int)cub->player.posx] == SPACE)
			cub->player.posy += cub->player.dirx * MOVESPEED;
	}
	if (movement == MOVE_LEFT)
	{
		if (cub->input.map.top_left[(int)cub->player.posy][(int) \
		(cub->player.posx + cub->player.diry * (MOVESPEED * 3))] == SPACE)
			cub->player.posx += cub->player.diry * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posy - cub->player.dirx
				* (MOVESPEED * 3))][(int)cub->player.posx] == SPACE)
			cub->player.posy -= cub->player.dirx * MOVESPEED;
	}
}

static void	rotate(t_cub3d *cub, float rotate)
{
	double	olddirx;
	double	oldplanex;

	rotate *= ROTSPEED;
	olddirx = cub->player.dirx;
	oldplanex = cub->player.planex;
	cub->player.dirx = cub->player.dirx * cos(rotate)
		- cub->player.diry * sin(rotate);
	cub->player.diry = olddirx * sin(rotate)
		+ cub->player.diry * cos(rotate);
	cub->player.planex = cub->player.planex * cos(rotate)
		- cub->player.planey * sin(rotate);
	cub->player.planey = oldplanex * sin(rotate)
		+ cub->player.planey * cos(rotate);
}

void	movement(t_cub3d *cub)
{
	if (cub->keys.up)
		move(cub, MOVE_UP);
	if (cub->keys.down)
		move(cub, MOVE_DOWN);
	if (cub->keys.left)
		strafe(cub, MOVE_LEFT);
	if (cub->keys.right)
		strafe(cub, MOVE_RIGHT);
	if (cub->keys.turn_left)
		rotate(cub, -1);
	if (cub->keys.turn_right)
		rotate(cub, 1);
}
