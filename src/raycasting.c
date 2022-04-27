/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:31:07 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lines(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cub->img.data[y * WIDTH + x] = cub->map_buff[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.img, 0, 0);
}

void	init_var(t_rc *rc)
{
	rc->camerax = 0;
	rc->raydirx = 0;
	rc->raydiry = 0;
	rc->mapx = 0;
	rc->mapy = 0;
	rc->sidedistx = 0;
	rc->sidedisty = 0;
	rc->deltadistx = 0;
	rc->deltadisty = 0;
	rc->perpwalldist = 0;
	rc->stepx = 0;
	rc->stepy = 0;
	rc->hit = 0;
	rc->side = 0;
	rc->lineheight = 0;
	rc->drawstart = 0;
	rc->drawend = 0;
	rc->texnum = 0;
	rc->wallx = 0;
	rc->texx = 0;
	rc->step = 0;
}

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
		//jump to next map square, OR in x-direction, OR in y-direction
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
		//Check if ray has hit a wall
		if (cub->input.map.top_left[rc->mapy][rc->mapx] == WALL)
			rc->hit = 1;
	}
}

void	wall_calcs(t_rc *rc, t_cub3d *cub)
{
		if (rc->side == 0)
			rc->perpwalldist = (rc->mapx - cub->player.posX + (1 - rc->stepx) / 2) / rc->raydirx;
		else
			rc->perpwalldist = (rc->mapy - cub->player.posY + (1 - rc->stepy) / 2) / rc->raydiry;
		
		rc->lineheight = (int)(HEIGHT / rc->perpwalldist);
		rc->drawstart = -rc->lineheight / 2 + HEIGHT / 2;
		if(rc->drawstart < 0)
			rc->drawstart = 0;
		rc->drawend = rc->lineheight / 2 + HEIGHT / 2;
		if(rc->drawend >= HEIGHT)
			rc->drawend = HEIGHT - 1;
		if (rc->side == 0)
			rc->wallx = cub->player.posY + rc->perpwalldist * rc->raydiry;
		else
			rc->wallx = cub->player.posX + rc->perpwalldist * rc->raydirx;
		rc->wallx -= floor(rc->wallx);

		// x coordinate on the texture
		rc->texx = (int)(rc->wallx * (double)TEXSIZE);
		if (rc->side == 0 && rc->raydirx > 0)
			rc->texx = TEXSIZE - rc->texx - 1;
		if (rc->side == 1 && rc->raydiry < 0)
			rc->texx = TEXSIZE - rc->texx - 1;

}


void	wall_drawing(t_rc *rc, t_cub3d *cub, const int x)
{
	double	texpos;
	int		y;
	int		texy;
	int		color;

	// How much to increase the texture coordinate perscreen pixel
	rc->step = 1.0 * TEXSIZE / rc->lineheight;
	// Starting texture coordinate
	texpos = (rc->drawstart - HEIGHT / 2 + rc->lineheight / 2) * rc->step;
	y = -1;
	printf("drawstart is %d, drawend is %d\n", rc->drawstart, rc->drawend);
	while (++y < rc->drawstart)
		cub->map_buff[y][x] = cub->input.ceiling.trgb;
	while (y < rc->drawend)
	{
		texy = (int)texpos & (TEXSIZE - 1);
		texpos += rc->step;
		color = cub->texture[TEXSIZE * texy + rc->texx];
		// if (rc->side == 1)
		// 	color = (color >> 1) & 8355711;
		cub->map_buff[y][x] = color;
		y++;
	}
	while (y++ < HEIGHT - 1)
		cub->map_buff[y][x] = cub->input.floor.trgb;
}

void	raycaster(t_cub3d *cub)
{
	t_rc	rc;
	int		x;

	ft_bzero(cub->map_buff, sizeof(int) * (WIDTH * HEIGHT));
	x = 0;
	while (x < WIDTH)
	{
		init_var(&rc);
		initial_calcs(&rc, cub, x);
		calc_sidedist(&rc, cub);
		dda_algo(&rc, cub);
		wall_calcs(&rc, cub);
		wall_drawing(&rc, cub, x);
		x++;
	}
}