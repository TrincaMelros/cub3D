/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/18 17:08:57 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_lines(t_cub3d *cub)
{
	int	y;
	int	x;

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
	mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window, cub->img.img, 0, 0);
}

void	raycaster(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		double	camerax;
		double	raydirx;
		double	raydiry;

		camerax = 2 * i / (double)WIDTH - 1;
		raydirx = cub->player.dirX + cub->player.planeX * camerax;
		raydiry = cub->player.dirY + cub->player.planeY * camerax;

		int	mapx;
		int	mapy;

		mapx = (int)cub->player.posX;
		mapy = (int)cub->player.posY;

		double sidedistx;
		double sidedisty;

		double deltadistx;
		double deltadisty;
		double perpwalldist;

		deltadistx = fabs(1 / raydirx);
		deltadisty = fabs(1 / raydiry);

		int stepx;
		int	stepy;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (cub->player.posX - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - cub->player.posX) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (cub->player.posY - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - cub->player.posY) * deltadisty;
		}

		int hit;
		int	side;

		hit = 0;
		side = 0;
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (cub->input.map.top_left[mapx][mapy] == WALL)
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (mapx - cub->player.posX + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (mapy - cub->player.posY + (1 - stepy) / 2) / raydiry;
		
		int lineheight;

		lineheight = (int)(HEIGHT / perpwalldist);

		int drawstart;
		int	drawend;

		drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;

		int	texnum;

		//texnum = cub->input.map.top_left[mapx][mapy];
		texnum = 0;

		double wallx;

		if(side == 0)
			wallx = cub->player.posY + perpwalldist * raydiry;
		else
			wallx = cub->player.posX + perpwalldist * raydirx;

		int	texx;

		texx = (int)(wallx * (double)TEXSIZE);
		if (side == 0 && raydirx > 0)
			texx = TEXSIZE - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = TEXSIZE - texx - 1;

		double step;

		step = 1.0 * TEXSIZE / lineheight;

		double texpos;

		texpos = (drawstart - HEIGHT / 2 + lineheight / 2) * step;

		int texy;
		int	color;
		int y;

		y = drawstart;
		while (y < drawend)
		{
			texy = (int)texpos & (TEXSIZE - 1);
			texpos += step;
			color = cub->texture[texnum][TEXSIZE * texy + texx];
			if (side == 1)
				color = (color >> 1) & 8355711;
			cub->map_buff[y][i] = color;
			y++;
		}
		i++;
	}
}