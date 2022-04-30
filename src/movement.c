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
		if (cub->input.map.top_left[(int)(cub->player.posY)][(int)
		(cub->player.posX + cub->player.dirX * (MOVESPEED * 3))] == SPACE)
			cub->player.posX += cub->player.dirX * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posY + cub->player.dirY
		* (MOVESPEED * 3))][(int)(cub->player.posX)] == SPACE)
			cub->player.posY += cub->player.dirY * MOVESPEED;
	}
	if (movement == MOVE_DOWN)
	{
		if (cub->input.map.top_left[(int)(cub->player.posY)][(int)
		(cub->player.posX - cub->player.dirX * (MOVESPEED * 3))] == SPACE)
			cub->player.posX -= cub->player.dirX * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posY - cub->player.dirY
		* (MOVESPEED * 3))][(int)(cub->player.posX)] == SPACE)
			cub->player.posY -= cub->player.dirY * MOVESPEED;
	}
}

static void	strafe(t_cub3d *cub, int movement)
{
	if (movement == MOVE_RIGHT)
	{
		if (cub->input.map.top_left[(int)(cub->player.posY)][(int)
		(cub->player.posX - cub->player.dirY * (MOVESPEED * 3))] == SPACE)
			cub->player.posX -= cub->player.dirY * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posY + cub->player.dirX
		* (MOVESPEED * 3))][(int)cub->player.posX] == SPACE)
			cub->player.posY += cub->player.dirX * MOVESPEED;
	}
	if (movement == MOVE_LEFT)
	{
		if (cub->input.map.top_left[(int)cub->player.posY][(int)
		(cub->player.posX + cub->player.dirY * (MOVESPEED * 3))] == SPACE)
			cub->player.posX += cub->player.dirY * MOVESPEED;
		if (cub->input.map.top_left[(int)(cub->player.posY - cub->player.dirX
		* (MOVESPEED * 3))][(int)cub->player.posX] == SPACE)
			cub->player.posY -= cub->player.dirX * MOVESPEED;
	}
}

static void	rotate(t_cub3d *cub, int rotate)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->player.dirX;
	oldplanex = cub->player.planeX;
	if (rotate == TURN_RIGHT)
	{
		cub->player.dirX = cub->player.dirX * cos(ROTSPEED)
		- cub->player.dirY * sin(ROTSPEED);
		cub->player.dirY = olddirx * sin(ROTSPEED) +
		cub->player.dirY * cos(ROTSPEED);
		cub->player.planeX = cub->player.planeX * cos(ROTSPEED)
		- cub->player.planeY * sin(ROTSPEED);
		cub->player.planeY = oldplanex * sin(ROTSPEED)
		+ cub->player.planeY * cos(ROTSPEED);
	}
	if (rotate == TURN_LEFT)
	{
		cub->player.dirX = cub->player.dirX * cos(-(ROTSPEED))
		- cub->player.dirY * sin(-(ROTSPEED));
		cub->player.dirY = olddirx * sin(-(ROTSPEED))
		+ cub->player.dirY * cos(-(ROTSPEED));
		cub->player.planeX = cub->player.planeX * cos(-(ROTSPEED))
		- cub->player.planeY * sin(-(ROTSPEED));
		cub->player.planeY = oldplanex * sin(-(ROTSPEED))
		+ cub->player.planeY * cos(-(ROTSPEED));
	}
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
		rotate(cub, TURN_LEFT);
	if (cub->keys.turn_right)
		rotate(cub, TURN_RIGHT);
}
