/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/14 15:06:39 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***************************AUXILIARY TEMPORARY FUNCTIONS*************************************/
void	print_input(char **print)
{
	int	i;

	i = -1;
	while (print[++i])
		printf("%s\n", print[i]);
}

void	print_path(t_input input)
{
	printf("NO -> %s\nSO -> %s\nWE -> %s\nEA -> %s\n", input.north, input.south, input.west, input.east);
}

void	print_RGB(t_input input)
{
	printf("floor red is %d\n", input.floor_R);
	printf("floor green is %d\n", input.floor_G);
	printf("floor blue is %d\n", input.floor_B);
	printf("ceiling red is %d\n", input.ceiling_R);
	printf("ceiling green is %d\n", input.ceiling_G);
	printf("ceiling blue is %d\n", input.ceiling_B);
}

void	print_map(t_input input)
{
	int i;

	i = -1;
	while (input.map[++i])
		printf("%s\n", input.map[i]);
}
/***************************AUXILIARY TEMPORARY FUNCTIONS*************************************/

static void	init_vars(t_input *input)
{
	input->north = NULL;
	input->south = NULL;
	input->west = NULL;
	input->east = NULL;
	input->floor_RGB = NULL;
	input->ceiling_RGB = NULL;
}

void	img_assignment(t_cub3d *cub)
{
	int		width;
	int		height;
	char	*path;

	path = "./assets/floor.xpm";
	cub->assets.floor = mlx_xpm_file_to_image(cub->mlx_obj.instance, path, &width, &height);
	path = "./assets/wall.xpm";
	cub->assets.wall = mlx_xpm_file_to_image(cub->mlx_obj.instance, path, &width, &height);
	path = "./assets/player.xpm";
	cub->assets.player = mlx_xpm_file_to_image(cub->mlx_obj.instance, path, &width, &height);
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
			if (cub->input.map[i][j] == '0')
				mlx_put_image_to_window(cub->mlx_obj.instance, cub->mlx_obj.window, \
						cub->assets.floor, j * 64, i * 64);
			else if (cub->input.map[i][j] == '1')
			{
				mlx_put_image_to_window(cub->mlx_obj.instance, cub->mlx_obj.window, \
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
			if (cub->input.map[i][j] == '0')
			{
				cub->assets.player_x = j * 64;
				cub->assets.player_x = j * 64;
				mlx_put_image_to_window(cub->mlx_obj.instance, cub->mlx_obj.window, cub->assets.player, j * 64, i * 64);
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

void	movement(t_cub3d *cub, int new_x, int new_y)
{
	int x;
	int	y;

	x = (new_x + 1) / 64;
	y = (new_y + 1) / 64;

	printf("y is %d, x is %d", y, x);
	if (cub->input.map[y][x] == '1')
		return;
	else
	{
		mlx_put_image_to_window(cub->mlx_obj.instance, cub->mlx_obj.window, cub->assets.floor, cub->assets.player_x / 64, cub->assets.player_y / 64);
		mlx_put_image_to_window(cub->mlx_obj.instance, cub->mlx_obj.window, cub->assets.player, new_x, new_y);	
	}
	cub->assets.player_x = new_x;
	cub->assets.player_x = new_y;
}

int	key_hook(int keycode, t_cub3d *cub)
{
	printf("MOVEMENT\n");
	if (keycode == MOVE_UP)
		movement(cub, cub->assets.player_y - 2, cub->assets.player_x);
	if (keycode == MOVE_DOWN)
		movement(cub, cub->assets.player_y + 2, cub->assets.player_x);
	if (keycode == MOVE_LEFT)
		movement(cub, cub->assets.player_y, cub->assets.player_x - 2);
	if (keycode == MOVE_RIGHT)
		movement(cub, cub->assets.player_y, cub->assets.player_x + 2);
	return (0);
}

int main(int argc, char **argv)
{
	t_cub3d	cub;

    if (argc != 2)
		error_general(OTHER, "Invalid number of arguments.");
	init_vars(&cub.input);
    if (map_parsing(argv[1], &cub.input))
		return (1);
	// print_input(cub.input.txt);
	// print_path(cub.input);
	// print_RGB(cub.input);
	print_map(cub.input);
	cub.mlx_obj.instance = mlx_init();
	cub.mlx_obj.window = mlx_new_window(cub.mlx_obj.instance, 640, 640, "Gamer");
	img_assignment(&cub);
	load_wall_floor(&cub);
	load_player(&cub);
	mlx_key_hook(cub.mlx_obj.window, key_hook, &cub);
	mlx_loop(cub.mlx_obj.instance);
	// free_all(&cub);
    return (0);
}