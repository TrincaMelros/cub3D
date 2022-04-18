/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:38:38 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/18 16:36:22 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_assignment(t_cub3d *cub)
{
	int		width;
	int		height;
	char	*path;

	path = "./assets/floor.xpm";
	cub->assets.floor = mlx_xpm_file_to_image(cub->mlx_obj.mlx, path, &width, &height);
	path = "./assets/wall.xpm";
	cub->assets.wall = mlx_xpm_file_to_image(cub->mlx_obj.mlx, path, &width, &height);
	path = "./assets/player.xpm";
	cub->assets.player = mlx_xpm_file_to_image(cub->mlx_obj.mlx, path, &width, &height);
}

void	load_wall_floor(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (cub->input.map.top_left[i][j] == SPACE)
				mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window,
						cub->assets.floor, j * 64, i * 64);
			else if (cub->input.map.top_left[i][j] == WALL)
			{
				mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window,
						cub->assets.wall, j * 64, i * 64);
			}
			j++;
		}
		i++;
	}
}

void	load_player(t_cub3d *cub)
{
	int	i;
	int	j;
	int	exit;

	exit = 0;
	i = 1;
	while (i < 10)
	{
		j = 1;
		while (j < 10)
		{
			if (cub->input.map.top_left[i][j] == SPACE)
			{
				cub->assets.player_x = j * 64;
				cub->assets.player_x = j * 64;
				mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window, cub->assets.player, j * 64, i * 64);
				exit = 1;
				break ;
			}
			j++;
		}
		if (exit)
			break ;
		i++;
	}
}