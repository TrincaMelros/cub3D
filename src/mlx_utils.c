/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:30:50 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/19 12:17:34 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_image(void *mlx_ptr, t_img *img, int width, int height)
{
	img->w = width;
	img->h = height;
	img->ptr = mlx_new_image(mlx_ptr, width, height);
	img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line, &img->endian);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_put_pixel(t_img *img, int color, int y, int x)
{
	img->addr[y * img->w + x] = color;
}

void	img_draw_verLine(t_img *img, int x, int y1, const int y2, int color)
{
	while (y1 <= y2)
	{
		img_put_pixel(img, color, y1, x);
		y1++;
	}
}

void	img_draw_horLine(t_img *img, int y, int x1, const int x2, int color)
{
	while (x1 <= x2)
	{
		img_put_pixel(img, color, y, x1);
		x1++;
	}
}