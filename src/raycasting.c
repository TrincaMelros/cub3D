/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:13 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/30 13:52:30 by fbarros          ###   ########.fr       */
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

static int	choose_texture(t_cub3d *cub, t_rc *rc, int texy)
{
	if (rc->side == 0)
	{
		if (cub->player.posx > rc->mapx)
			return (cub->textures.west[TEXSIZE * texy + rc->texx]);
		else
			return (cub->textures.east[TEXSIZE * texy + rc->texx]);
	}
	else
	{
		if (cub->player.posy > rc->mapy)
			return (cub->textures.north[TEXSIZE * texy + rc->texx]);
		else
			return (cub->textures.south[TEXSIZE * texy + rc->texx]);
	}
}

static void	wall_drawing(t_rc *rc, t_cub3d *cub, const int x)
{
	double	texpos;
	int		y;
	int		texy;
	int		color;

	rc->step = 1.0 * TEXSIZE / rc->lineheight;
	texpos = (rc->drawstart - HEIGHT / 2 + rc->lineheight / 2) * rc->step;
	y = -1;
	while (++y < rc->drawstart)
		cub->map_buff[y][x] = cub->input.ceiling.trgb;
	while (y < rc->drawend)
	{
		texy = (int)texpos & (TEXSIZE - 1);
		texpos += rc->step;
		color = choose_texture(cub, rc, texy);
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
		ft_bzero(&rc, sizeof(t_rc));
		initial_calcs(&rc, cub, x);
		calc_sidedist(&rc, cub);
		dda_algo(&rc, cub);
		wall_calcs(&rc, cub);
		wall_drawing(&rc, cub, x);
		x++;
	}
}
