/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/30 13:32:50 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *cub)
{
	ft_bzero(cub, sizeof(t_cub3d));
	cub->input.floor.trgb = -1;
	cub->input.ceiling.trgb = -1;
}

void	free_all(t_cub3d *cub)
{
	if (cub->layers.screen.img)
		mlx_destroy_image(cub->mlx, cub->layers.screen.img);
	if (cub->layers.minimap.img)
		mlx_destroy_image(cub->mlx, cub->layers.minimap.img);
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	if (cub->input.txt)
		twod_free((void **)cub->input.txt, 0);
	if (cub->input.map.top_left)
		twod_free((void **)cub->input.map.top_left, cub->input.map.h);
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

int	main_loop(t_cub3d *cub)
{
	movement(cub);
	raycaster(cub);
	draw_lines(cub);
	return (0);
}

int	main(int argc, char **argv)
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
	cub_parsing(argv[1], &(get_data(NULL)->input));
	set_game(&cub3d);
	mlx_loop(cub3d.mlx);
}
