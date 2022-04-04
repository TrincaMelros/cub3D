/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/04 21:25:37 by fbarros          ###   ########.fr       */
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
	printf("floor red is %d\n", input.floor.r);
	printf("floor green is %d\n", input.floor.g);
	printf("floor blue is %d\n", input.floor.b);
	printf("floor trgb is %d\n", input.floor.trgb);
	printf("ceiling red is %d\n", input.ceiling.r);
	printf("ceiling green is %d\n", input.ceiling.g);
	printf("ceiling blue is %d\n", input.ceiling.b);
	printf("ceiling trgb is %d\n", input.ceiling.trgb);
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
	obj->input.floor.trgb = -1;
	obj->input.ceiling.trgb = -1;
}

static void	free_all(t_cub3d *obj)
{
	twod_free((void **)obj->input.txt);
}

static void	check_ftype(const char *ftype)
{
	char	*cptr;

	cptr = ft_strchr(ftype, '.');
	if (ft_strlen(cptr) != 4 || !ft_strnstr(cptr, "cub", 4))
		ft_error("Wrong file type.");
}

t_cub3d *get_data(t_cub3d *original) {
	static t_cub3d *data = NULL;
	if (original != NULL) {
		data = original;
	}
	return (data);
}

int main(int argc, char **argv)
{
	t_cub3d	cub3d;

    if (argc != 2)
	{
		ft_error("Invalid number of arguments.");
		return (1);
	}
	check_ftype(argv[1]);
	ft_init(&cub3d);
	get_data(&cub3d);
    map_parsing(argv[1], &(get_data(NULL)->input));
	DEBUG(print_input(cub3d.input.txt);)
	DEBUG(print_RGB(cub3d.input);)
	// cub3d.mlx_obj.mlx = mlx_init();
	// cub3d.mlx_obj.window = mlx_new_window(cub3d.mlx_obj.mlx, WIDTH, HEIGHT, "Cub3D");
	// // mlx_loop_hook(cub3d.mlx_obj.mlx, &raycast(mlx_obj ??), &cub3d);
	// mlx_loop(cub3d.mlx_obj.mlx);
	// mlx_destroy_window(cub3d.mlx_obj.mlx, cub3d.mlx_obj.window);
	free_all(&cub3d);
    return (0);
}
