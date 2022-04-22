/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/22 17:50:18 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init(t_cub3d *cub)
{
	ft_bzero(cub, sizeof(t_cub3d));
	cub->input.floor.trgb = -1;
	cub->input.ceiling.trgb = -1;
	cub->player.posX = cub->input.map.player.x;
	cub->player.posY = cub->input.map.player.y;
	cub->player.dirX = -1;
	cub->player.dirY = 0;
}

void	free_all(t_cub3d *cub3d)
{
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	twod_free((void **)cub3d->input.txt);
	twod_free((void **)cub3d->input.map.top_left);
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

void	set_images(void *mlx_ptr, t_images *imgs)
{
	imgs->screen.ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	imgs->screen.addr = (int *)mlx_get_data_addr(imgs->screen.ptr, &imgs->screen.bpp, &imgs->screen.line, &imgs->screen.endian);
}

int	main_loop(t_cub3d *cub)
{
	redraw_player(cub);
	movement(cub);
	return (0);
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
	// DEBUG(init_test(&cub3d);)
	cub_parsing(argv[1], &cub3d.input);

	set_game(&cub3d);

	// mlx_hook(cub3d.window, 2, 1L<<0, key_events, &cub3d);
	mlx_hook(cub3d.window, 2, 0, key_events, &cub3d);
	
	DEBUG(init_test(&cub3d);)

    cub_parsing(argv[1], &(get_data(NULL)->input));

	// mlx_hook(cub3d.window, 4, 1L<<15, button_press, &cub3d);
	// mlx_key_hook(cub3d.window, key_events, &cub3d);
	mlx_loop_hook(cub3d.mlx, &main_loop, &cub3d);
	mlx_loop(cub3d.mlx);

	cub3d.mlx = mlx_init();
	cub3d.window = mlx_new_window(cub3d.mlx, cub3d.input.map.w * 64, cub3d.input.map.h * 64, "Cub3D");
	

	minimap_launcher(&cub3d);
	mlx_loop_hook(cub3d.mlx, &main_loop, &cub3d);
	// mlx_hook(cub3d.window, X_EVENT_KEY_PRESS, 0, &key_press, &cub3d); // kinda copied from l-yohai
	mlx_hook(cub3d.window, X_BUTTON_EXIT, 131072, &key_close, &cub3d);
	mlx_hook(cub3d.window, 02, 0, &key_press, &cub3d);
	mlx_hook(cub3d.window, 03, 0, &key_release, &cub3d);

	mlx_loop(cub3d.mlx);
	
	mlx_destroy_window(cub3d.mlx, cub3d.window);
	free_all(&cub3d);
}
