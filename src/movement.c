/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:58 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/18 11:50:24 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement(t_cub3d *cub, int new_x, int new_y)
{
	int x;
	int	y;

	x = (new_x + 1) / 64;
	y = (new_y + 1) / 64;

	printf("y is %d, x is %d", y, x);
	if (cub->input.map.top_left[y][x] == WALL)
		return;
	else
	{
		mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window, cub->assets.floor, cub->assets.player_x / 64, cub->assets.player_y / 64);
		mlx_put_image_to_window(cub->mlx_obj.mlx, cub->mlx_obj.window, cub->assets.player, new_x, new_y);	
	}
	cub->assets.player_x = new_x;
	cub->assets.player_x = new_y;
}

void	redraw_player(t_cub3d *cub)
{
	int	test;

	test = (int)cub->player.posX;
	load_wall_floor(cub);
	load_player(cub, 0);

}

int	key_hook(int keycode, t_cub3d *cub)
{
	 double moveSpeed = 0.5;
	 double rotSpeed = 0.5;

	printf("MOVEMENT\n");
    if (keycode == MOVE_UP)
    {
    	if(cub->input.map.top_left[(int)(cub->player.posX + cub->player.dirX * moveSpeed)][(int)(cub->player.posY)] == SPACE)
			cub->player.posX += cub->player.dirX * moveSpeed;
    	if(cub->input.map.top_left[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.dirY * moveSpeed)] == SPACE)
			cub->player.posY += cub->player.dirY * moveSpeed;
    }
    if (keycode == MOVE_DOWN)
    {
    	if(cub->input.map.top_left[(int)(cub->player.posX - cub->player.dirX * moveSpeed)][(int)(cub->player.posY)] == SPACE)
			cub->player.posX -= cub->player.dirX * moveSpeed;
    	if(cub->input.map.top_left[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.dirY * moveSpeed)] == SPACE)
			cub->player.posY -= cub->player.dirY * moveSpeed;
    }
	if (keycode == MOVE_RIGHT)
	{
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(-rotSpeed) - cub->player.dirY * sin(-rotSpeed);
		cub->player.dirY = oldDirX * sin(-rotSpeed) + cub->player.dirY * cos(-rotSpeed);
	}
	if (keycode == MOVE_LEFT)
	{
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(rotSpeed) - cub->player.dirY * sin(rotSpeed);
		cub->player.dirY = oldDirX * sin(rotSpeed) + cub->player.dirY * cos(rotSpeed);
	}
	redraw_player(cub);
	return (0);
}
