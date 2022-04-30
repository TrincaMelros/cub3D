/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/29 12:16:33 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_color(char *txt, t_color *color)
{
	char	**splitter;
	int		i;

	i = -1;
	splitter = ft_split(txt, ',');
	if (color->trgb > -1)
		free_error_exit(".cub: color assigned more than once.");
	while (splitter[++i])
		continue ;
	if (i == 3)
	{
		color->r = ft_atoi(splitter[0]);
		color->g = ft_atoi(splitter[1]);
		color->b = ft_atoi(splitter[2]);
		color->trgb = create_trgb(0, color->r, color->g, color->b);
		i = 0;
	}
	else
		free_error_exit(".cub: must assign 3 values to color.");
	twod_free((void **)splitter, 0);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		free_error_exit(".cub: color value too damn high.");
	if (color->r < 0 || color->g < 0 || color->b < 0)
		free_error_exit(".cub: color value too low.");
}

static char	**assign_elements(t_input *input)
{
	static char	**ptr;

	ptr = input->txt;
	while (ptr && *ptr && !all_assigned(input))
	{
		if (!strncmp(*ptr, "NO", 2))
			assign_texture(&input->north, *ptr + 3);
		else if (!strncmp(*ptr, "SO", 2))
			assign_texture(&input->south, *ptr + 3);
		else if (!strncmp(*ptr, "EA", 2))
			assign_texture(&input->east, *ptr + 3);
		else if (!strncmp(*ptr, "WE", 2))
			assign_texture(&input->west, *ptr + 3);
		else if (!strncmp(*ptr, "F", 1))
			assign_color(*ptr + 1, &input->floor);
		else if (!strncmp(*ptr, "C", 1))
			assign_color(*ptr + 1, &input->ceiling);
		else if (!line_empty(*ptr))
			free_error_exit(".cub: invalid or missing element.");
		ptr++;
	}
	if (!all_assigned(input))
		return (NULL);
	return (ptr);
}

static char	**get_input(char *file)
{
	char		**txt;
	int			fd;
	int			rd;
	static int	i;

	txt = calloc_check(1, sizeof(char *));
	fd = open(file, O_RDONLY);
	rd = 1;
	while (rd == 1)
	{
		rd = get_next_line(&txt[i++], fd);
		txt = (char **)twod_realloc((void **)txt, 1);
		if (!txt)
			free_error_exit(NULL);
	}
	if (rd < 0)
	{
		if (fd > 2)
			close(fd);
		free_error_exit(NULL);
	}
	return (txt);
}

void	cub_parsing(char *filename, t_input *input)
{
	char	**map;

	input->txt = get_input(filename);
	map = assign_elements(input);
	if (!map)
		free_error_exit(".cub: File data invalid or missing.");
	while (map && *map && line_empty(*map))
		map++;
	if (!map || !*map)
		free_error_exit("map: invalid, missing or not well positioned.");
	if (ft_strset(*map, "NSEWCF"))
		free_error_exit(".cub: element assigned more than once.");
	input->map = map_validation(map);
}
