/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:05:59 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub3d *cub, int movement)
{
	if (movement == UP)
	{
	    if(cub->input.map.top_left[(int)(cub->player.posY)][(int)(cub->player.posX + cub->player.dirX * MOVESPEED)] == SPACE)
			cub->player.posX += cub->player.dirX * MOVESPEED;
    	if(cub->input.map.top_left[(int)(cub->player.posY + cub->player.dirY * MOVESPEED)][(int)(cub->player.posX)] == SPACE)
			cub->player.posY += cub->player.dirY * MOVESPEED;	
	}
	if (movement == DOWN)
	{
		if(cub->input.map.top_left[(int)(cub->player.posX - cub->player.dirX * MOVESPEED)][(int)(cub->player.posY)] == SPACE)
			cub->player.posX -= cub->player.dirX * MOVESPEED;
    	if(cub->input.map.top_left[(int)(cub->player.posY - cub->player.dirY * MOVESPEED)][(int)(cub->player.posX)] == SPACE)
			cub->player.posY -= cub->player.dirY * MOVESPEED;	
	}
}

void	rotate(t_cub3d *cub, int rotate)
{
	double	olddirx;
	double	oldplanex;
	
	olddirx = 0;
	if (rotate == LEFT)
	{
		olddirx = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(ROTSPEED) - cub->player.dirY * sin(ROTSPEED);
		cub->player.dirY = olddirx * sin(ROTSPEED) + cub->player.dirY * cos(ROTSPEED);
		oldplanex = cub->player.planeX;
		cub->player.planeX = cub->player.planeX * cos(ROTSPEED) - cub->player.planeY * sin(ROTSPEED);
		cub->player.planeY = oldplanex * sin(ROTSPEED + cub->player.planeY * cos(ROTSPEED));	
	}
	if (rotate == RIGHT)
	{
		olddirx = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(-(ROTSPEED)) - cub->player.dirY * sin(-(ROTSPEED));
		cub->player.dirY = olddirx * sin(-(ROTSPEED)) + cub->player.dirY * cos(-(ROTSPEED));
		oldplanex = cub->player.planeX;
		cub->player.planeX = cub->player.planeX * cos(-(ROTSPEED)) - cub->player.planeY * sin(-(ROTSPEED));
		cub->player.planeY = oldplanex * sin(-(ROTSPEED)) + cub->player.planeY * cos(-(ROTSPEED));
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
