/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/28 14:57:03 by fbarros          ###   ########.fr       */
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

void	print_RGB(const t_input input)
{
	printf("floor red is %d\n", input.floor.R);
	printf("floor green is %d\n", input.floor.G);
	printf("floor blue is %d\n", input.floor.B);
	printf("floor trgb is %d\n", input.floor.TRGB);
	printf("ceiling red is %d\n", input.ceiling.R);
	printf("ceiling green is %d\n", input.ceiling.G);
	printf("ceiling blue is %d\n", input.ceiling.B);
	printf("ceiling trgb is %d\n", input.ceiling.TRGB);
}

void	print_map(t_input input)
{
	int i;

	i = -1;
	while (input.map[++i])
		printf("%s\n", input.map[i]);
}
/***************************AUXILIARY TEMPORARY FUNCTIONS*************************************/

static void	ft_init(t_cub3d *obj)
{
	ft_memset(obj, 0, sizeof(t_cub3d));
	obj->input.floor.TRGB = -1;
	obj->input.ceiling.TRGB = -1;
}

static void	free_all(t_cub3d *obj)
{
	twoD_free((void **)&obj->input.txt);
	
}

int main(int argc, char **argv)
{
	t_cub3d	cub3d;

    if (argc != 2)
		ft_error("Invalid number of arguments.");
	ft_init(&cub3d);
    if (map_parsing(argv[1], &cub3d.input))
		return (1);
	// cub3d.mlx_obj.mlx = mlx_init();
	// cub3d.mlx_obj.window = mlx_new_window(cub3d.mlx_obj.mlx, WIDTH, HEIGHT, "Cub3D");
	// // mlx_loop_hook(cub3d.mlx_obj.mlx, &raycast(mlx_obj ??), &cub3d);
	// mlx_loop(cub3d.mlx_obj.mlx);
	// mlx_destroy_window(cub3d.mlx_obj.mlx, cub3d.mlx_obj.window);
	free_all(&cub3d);
    return (0);
}