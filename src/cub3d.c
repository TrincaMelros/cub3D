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

static void	twoD_free(void **ptr_arr)
{
	while (*ptr_arr)
	{
		free(*ptr_arr);
		*ptr_arr++ = NULL;
	}
}

static void	free_all(t_cub3d *obj)
{
	twoD_free((void **)obj->input.txt);
	// ...
}

static void	init_vars(t_input *input)
{
	input->north = NULL;
	input->south = NULL;
	input->west = NULL;
	input->east = NULL;
	input->floor_RGB = NULL;
	input->ceiling_RGB = NULL;
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
	// print_map(cub.input);

	free_all(&cub);
    return (0);
}