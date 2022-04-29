/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/29 12:54:24 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *cub)
{
	ft_bzero(cub, sizeof(t_cub3d));
	cub->input.floor.trgb = -1;
	cub->input.ceiling.trgb = -1;
	// cub->player.posX = cub->input.map.player.x;
	// cub->player.posY = cub->input.map.player.y;
	// cub->player.dirX = -1;
	// cub->player.dirY = 0;
}

void	free_all(t_cub3d *cub)
{
	if (cub->layers.screen.ptr)
		mlx_destroy_image(cub->mlx, cub->layers.screen.ptr);
	if (cub->layers.minimap.ptr)
		mlx_destroy_image(cub->mlx, cub->layers.minimap.ptr);
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

// void	set_images(void *mlx_ptr, t_layers *imgs)
// {
// 	imgs->screen.ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
// 	imgs->screen.addr = (int *)mlx_get_data_addr(imgs->screen.ptr, &imgs->screen.bpp, &imgs->screen.line, &imgs->screen.endian);
// }

// int	main_loop(t_cub3d *cub)
// {
// 	// redraw_player(cub);
// 	movement(cub);
// 	return (0);
// }

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
	// make independent, copy whatever's relevant to cub struct and get rid of it
    cub_parsing(argv[1], &(get_data(NULL)->input));
	free_all(&cub3d);
	set_game(&cub3d); // <------------------ set_game(&cub, &input);
	mlx_loop(cub3d.mlx);
	return (0);
}
