/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:30:50 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:14:42 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_image(void *mlx_ptr, t_img *img, int width, int height)
{
	img->w = width;
	img->h = height;
	img->ptr = mlx_new_image(mlx_ptr, width, height);
	if (!img->ptr)
		free_error_exit(NULL);
	img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line, &img->endian);
	if (!img->addr)
		free_error_exit(NULL);
}

<<<<<<< HEAD
//void	img_put_pixel(t_img *img, int color, int y, int x) 
//{
//    img->addr[y * img->w + x] = color;
//}

//void	img_draw_verLine(t_img *img, int x, int y1, int y2, int color)
//{
//	int	y;
//
//	y = y1;
//	while (y <= y2)
//	{
//		img_put_pixel(img, color, y, x);
//		y++;
//	}
//}
=======
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_put_pixel(t_img *img, int color, int y, int x)
{
	img->addr[y * img->w + x] = color;
}
>>>>>>> origin/barros

int	key_close(int keycode, t_cub3d *cub3d)
{
	(void)keycode;
	mlx_destroy_window(cub3d->mlx, cub3d->window);
	free_all(cub3d);
	exit(0);
}