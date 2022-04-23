/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:55:12 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/23 14:55:13 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_cub3d *cub, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = (int *)malloc(sizeof(int) * (TEXSIZE * TEXSIZE));
	img->img = mlx_xpm_file_to_image(cub->mlx_obj.mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(cub->mlx_obj.mlx, img->img);
}

void	load_texture(t_cub3d *cub)
{
	t_img img;

	load_image(cub, cub->texture[0], "assets/brickwall.xpm", &img);
}