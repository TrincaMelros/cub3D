/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:07:45 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:47:59 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_point coord, const t_point size, int color, t_img *img)
{
	int	x;

	x = coord.x;
	while (coord.x < x + size.x)
	{
		img_draw_verline(img, coord, coord.y + size.y - 1, color);
		coord.x++;
	}
}

void	img_draw_verline(t_img *img, t_point p, const int y2, int color)
{
	while (p.y <= y2)
	{
		img_put_pixel(img, color, p.y, p.x);
		p.y++;
	}
}

void	img_draw_horline(t_img *img, t_point p, const int x2, int color)
{
	while (p.x <= x2)
	{
		img_put_pixel(img, color, p.y, p.x);
		p.x++;
	}
}
