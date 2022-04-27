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

<<<<<<< HEAD
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
void	calc_sidedist(t_cub3d *cub)
{
	//	calculate step and initial sideDist, which is the length of ray from the current position to the next x or y side
	if (cub->rc.raydirx < 0)
	{
		cub->rc.stepx = -1;
		cub->rc.sidedistx = (cub->player.posX - cub->rc.mapx) * cub->rc.deltadistx;
	}
	else
	{
		cub->rc.stepx = 1;
		cub->rc.sidedistx = (cub->rc.mapx + 1.0 - cub->player.posX) * cub->rc.deltadistx;
	}
	if (cub->rc.raydiry < 0)
	{
		cub->rc.stepy = -1;
		cub->rc.sidedisty = (cub->player.posY - cub->rc.mapy) * cub->rc.deltadisty;
	}
	else
	{
		cub->rc.stepy = 1;
		cub->rc.sidedisty = (cub->rc.mapy + 1.0 - cub->player.posY) * cub->rc.deltadisty;
	}
}

void	initial_calcs(t_cub3d *cub, int i)
{
	//	camerax goes from -1 to 1, represents x-coordinate on the camera plane.
		cub->rc.camerax = 2 * i / (double)WIDTH - 1;
	//	raydir is the direction of the ray we're casting.
		cub->rc.raydirx = cub->player.dirX + cub->player.planeX * cub->rc.camerax;
		cub->rc.raydiry = cub->player.dirY + cub->player.planeY * cub->rc.camerax;
	//	mapx and mapy represent the square of the map we're in.
		cub->rc.mapx = (int)cub->player.posX;
		cub->rc.mapy = (int)cub->player.posY;
	//	length of the ray from one x or y side to the next x or y side.
		cub->rc.deltadistx = fabs(1 / cub->rc.raydirx);
		cub->rc.deltadisty = fabs(1 / cub->rc.raydiry);

}

void	dda_algorith(t_cub3d *cub)
{
		while (cub->rc.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (cub->rc.sidedistx < cub->rc.sidedisty)
			{
				cub->rc.sidedistx += cub->rc.deltadistx;
				cub->rc.mapx += cub->rc.stepx;
				cub->rc.side = 0;
			}
			else
			{
				cub->rc.sidedisty += cub->rc.deltadisty;
				cub->rc.mapy += cub->rc.stepy;
				cub->rc.side = 1;
			}
			//Check if ray has hit a wall
			if (cub->input.map.top_left[cub->rc.mapx][cub->rc.mapy] == WALL)
				cub->rc.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect)
		if (cub->rc.side == 0)
			cub->rc.perpwalldist = (cub->rc.mapx - cub->player.posX + (1 - cub->rc.stepx) / 2) / cub->rc.raydirx;
		else
			cub->rc.perpwalldist = (cub->rc.mapy - cub->player.posY + (1 - cub->rc.stepy) / 2) / cub->rc.raydiry;
		
}
void	wall_calcs(t_cub3d *cub)
{
	//Calculate height of line to draw on screen
	cub->rc.lineheight = (int)(HEIGHT / cub->rc.perpwalldist);
	//Calculate lowest and highest pixel to fill in current stripe
	cub->rc.drawstart = -cub->rc.lineheight / 2 + HEIGHT / 2;
	if (cub->rc.drawstart < 0)
		cub->rc.drawstart = 0;
	cub->rc.drawend = cub->rc.lineheight / 2 + HEIGHT / 2;
	if (cub->rc.drawend >= HEIGHT)
		cub->rc.drawend = HEIGHT - 1;
    //Texturing calculations	
	cub->rc.texnum = cub->input.map.top_left[cub->rc.mapx][cub->rc.mapy];
	//calculate value of wallX, where the wall was hit
	if(cub->rc.side == 0)
		cub->rc.wallx = cub->player.posY + cub->rc.perpwalldist * cub->rc.raydiry;
	else
		cub->rc.wallx = cub->player.posX + cub->rc.perpwalldist * cub->rc.raydirx;
	//x coordinate on the texture	
	cub->rc.texx = (int)(cub->rc.wallx * (double)TEXSIZE);
	if (cub->rc.side == 0 && cub->rc.raydirx > 0)
		cub->rc.texx = TEXSIZE - cub->rc.texx - 1;
	if (cub->rc.side == 1 && cub->rc.raydiry < 0)
		cub->rc.texx = TEXSIZE - cub->rc.texx - 1;
	// How much to increase the texture coordinate per screen pixel
	cub->rc.step = 1.0 * TEXSIZE / cub->rc.lineheight;

}

void	wall_drawing(t_cub3d *cub, int i)
{
	double	texpos;
	int 	texy;
	int		color;
	int		y;	

	texpos = (cub->rc.drawstart - HEIGHT / 2 + cub->rc.lineheight / 2) * cub->rc.step;
	y = cub->rc.drawstart;
	while (y < cub->rc.drawend)
	{
		texy = (int)texpos & (TEXSIZE - 1);
		texpos += cub->rc.step;
		color = cub->texture[cub->rc.texnum][TEXSIZE * texy + cub->rc.texx];
		if (cub->rc.side == 1)
		{
			color = (color >> 1) & 8355711;
			cub->map_buff[y][i] = color;
			y++;
		}
	}
}
void	set_vars (t_rc *rc)
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

void	raycaster(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		set_vars(&(cub->rc));
		initial_calcs(cub, i);
		calc_sidedist(cub);
		dda_algorith(cub);
		wall_calcs(cub);
		wall_drawing(cub, i);
		i++;
	}
}
=======
int	main_loop(/* void *params */t_cub3d *cub3d)
{
	// raycast
	// mlx_put_image_to_window(cub3d->mlx, cub3d->window,
	// 	cub3d->layers.screen.ptr, 0, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window,
		cub3d->layers.minimap.ptr, 10, 10);
	return (SUCCESS);
}
>>>>>>> origin/barros
