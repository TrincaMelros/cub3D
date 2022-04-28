/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/25 14:05:36 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *cub)
{
	ft_bzero(cub, sizeof(t_cub3d));
	cub->input.floor.trgb = -1;
	cub->input.ceiling.trgb = -1;

}

void	init_vars(t_cub3d *cub)
{
	int	i;

	cub->player.posX = cub->input.map.player.x;
	cub->player.posY = cub->input.map.player.y;
	cub->player.dirX = -1.0;
	cub->player.dirY = 0.0;
	cub->player.planeX = 0.0;
	cub->player.planeY = 0.66;
	// olhar para estas alocacoes
	cub->texture = (int *)malloc(sizeof(int) * (TEXSIZE * TEXSIZE));
	i = 0;
	while(i < TEXSIZE * TEXSIZE)
	{
		cub->texture[i] = 0;
		i++;
	}
}

void	free_all(t_cub3d *cub)
{
	if (cub->layers.screen.img)
		mlx_destroy_image(cub->mlx, cub->layers.screen.img);
	if (cub->layers.minimap.img)
		mlx_destroy_image(cub->mlx, cub->layers.minimap.img);
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	twod_free((void **)cub->input.txt);
	twod_free((void **)cub->input.map.top_left);
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

//void	set_images(void *mlx_ptr, t_images *imgs)
//{
//	imgs->screen.ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
//	imgs->screen.addr = (int *)mlx_get_data_addr(imgs->screen.ptr, &imgs->screen.bpp, &imgs->screen.line, &imgs->screen.endian);
//}

int	main_loop(t_cub3d *cub)
{
	movement(cub);
	raycaster(cub);
	draw_lines(cub);
	return (0);
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

    cub_parsing(argv[1], &(get_data(NULL)->input));
	init_vars(&cub3d);
	
	set_game(&cub3d);

	build_image(cub3d.mlx, &cub3d.img, WIDTH, HEIGHT);

	load_texture(&cub3d);
	mlx_loop_hook(cub3d.mlx, &main_loop, &cub3d);
//	mlx_hook(cub3d.window, X_BUTTON_EXIT, (1L << 17), &free_and_quit, &cub3d); //need to replace free_and_quit with a similar one that returns int*
	mlx_hook(cub3d.window, KEY_PRESS, 0, &key_press, &cub3d);
	mlx_hook(cub3d.window, KEY_RELEASE, 0, &key_release, &cub3d);

	mlx_loop(cub3d.mlx);
	
//	mlx_destroy_window(cub3d.mlx, cub3d.window);
//	free_all(&cub3d);
}
