/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:50:51 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/29 12:50:52 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_calcs(t_rc *rc, t_cub3d *cub, int x)
{
	rc->camerax = 2 * x / (double)WIDTH - 1;
	rc->raydirx = cub->player.dirX + cub->player.planeX * rc->camerax;
	rc->raydiry = cub->player.dirY + cub->player.planeY * rc->camerax;
	rc->mapx = (int)cub->player.posX;
	rc->mapy = (int)cub->player.posY;
	rc->deltadistx = fabs(1 / rc->raydirx);
	rc->deltadisty = fabs(1 / rc->raydiry);
}

void	calc_sidedist(t_rc *rc, t_cub3d *cub)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (cub->player.posX - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - cub->player.posX) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (cub->player.posY - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - cub->player.posY) * rc->deltadisty;
	}
}

void	dda_algo(t_rc *rc, t_cub3d *cub)
{
	while (rc->hit == 0)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltadistx;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->deltadisty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (cub->input.map.top_left[rc->mapy][rc->mapx] == WALL)
			rc->hit = 1;
	}
}

void	wall_calcs(t_rc *rc, t_cub3d *cub)
{
	if (rc->side == 0)
		rc->perpwalldist = (rc->mapx - cub->player.posX + \
		(1 - rc->stepx) / 2) / rc->raydirx;
	else
		rc->perpwalldist = (rc->mapy - cub->player.posY + \
		(1 - rc->stepy) / 2) / rc->raydiry;
	rc->lineheight = (int)(HEIGHT / rc->perpwalldist);
	rc->drawstart = -rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawend >= HEIGHT)
		rc->drawend = HEIGHT - 1;
	if (rc->side == 0)
		rc->wallx = cub->player.posY + rc->perpwalldist * rc->raydiry;
	else
		rc->wallx = cub->player.posX + rc->perpwalldist * rc->raydirx;
	rc->wallx -= floor(rc->wallx);
	rc->texx = (int)(rc->wallx * (double)TEXSIZE);
	if (rc->side == 0 && rc->raydirx > 0)
		rc->texx = TEXSIZE - rc->texx - 1;
	if (rc->side == 1 && rc->raydiry < 0)
		rc->texx = TEXSIZE - rc->texx - 1;
}