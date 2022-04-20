/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/20 12:21:24 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *obj)
{
	ft_memset(obj, 0, sizeof(t_cub3d));
	obj->input.floor.trgb = -1;
	obj->input.ceiling.trgb = -1;
}

void	free_all(t_cub3d *obj)
{
	mlx_destroy_window(obj->mlx_obj.mlx, obj->mlx_obj.window);
	twod_free((void **)obj->input.txt);
	twod_free((void **)obj->input.map.top_left);
}

static void	check_ftype(const char *ftype)
{
	char	*cptr;

	cptr = ft_strchr(ftype, '.');
	if (cptr[1] == '/')
		cptr = ft_strchr(cptr + 1, '.');
	if (ft_strlen(cptr) != 4 || !ft_strnstr(cptr, "cub", 4))
		error_exit("Wrong file type.");
}

int main(int argc, char **argv)
{
	t_cub3d	cub3d;

    if (argc != 2)
	{
		ft_error("Invalid number of arguments.");
		return (OTHER);
	}
	check_ftype(argv[1]);
	ft_init(&cub3d);
	get_data(&cub3d);
	DEBUG(init_test(&cub3d);)
	cub_parsing(argv[1], &cub3d.input);

	set_game(&cub3d);

	mlx_loop_hook(cub3d.mlx_obj.mlx, &main_loop, &cub3d);
	mlx_loop(cub3d.mlx_obj.mlx);

	free_all(&cub3d);
}
