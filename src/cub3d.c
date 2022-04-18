/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/18 11:54:56 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *obj)
{
	ft_bzero(obj, sizeof(t_cub3d));
	obj->input.floor.trgb = -1;
	obj->input.ceiling.trgb = -1;
}

void	free_all(t_cub3d *cub3d)
{
	twod_free((void **)cub3d->input.txt);
	twod_free((void **)cub3d->input.map.top_left);
}

static void	check_ftype(const char *ftype)
{
	char	*cptr;

	cptr = ft_strchr(ftype, '.');
	if (ft_strlen(cptr) != 4 || !ft_strnstr(cptr, "cub", 4))
		error_exit("Wrong file type.");
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
	
	DEBUG(init_test(&cub3d);)

    cub_parsing(argv[1], &(get_data(NULL)->input));
	// DEBUG(print_txt(cub3d.input.txt);)
	// cub3d.mlx_obj.window = mlx_new_window(cub3d.mlx_obj.mlx, WIDTH, HEIGHT, "Cub3D");
	// // mlx_loop_hook(cub3d.mlx_obj.mlx, &raycast(mlx_obj ??), &cub3d);
	// cub3d.mlx_obj.mlx = mlx_init();
	// cub3d.mlx_obj.window = mlx_new_window(cub3d.mlx_obj.mlx, 640, 640, "Gamer");
	// img_assignment(&cub3d);
	// load_wall_floor(&cub3d);
	// load_player(&cub3d);
	// mlx_key_hook(cub3d.mlx_obj.window, key_hook, &cub3d);
	// mlx_loop(cub3d.mlx_obj.mlx);
	// mlx_destroy_window(cub3d.mlx_obj.mlx, cub3d.mlx_obj.window);
	free_all(&cub3d);
    return (0);
}
