/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/14 19:26:53 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	assign_color(char *txt, t_color *color)
{
	int		i;
	char	**splitter;

	i = -1;
	splitter = ft_split(txt, ',');
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
		i = -1;
	twod_free((void **)splitter);
	if (color->r > 255 || color->g > 255 || color->b > 255
		|| color->r < 0 || color->g < 0 || color->b < 0)
			i = -1;
	return (i);
}

static int	all_assigned(t_input *input)
{
	if (input->north == NULL)
		return (0);
	if (input->south == NULL)
		return (0);
	if (input->west == NULL)
		return (0);
	if (input->east == NULL)
		return (0);
	if (input->floor.trgb == -1)
		return (0);
	if (input->ceiling.trgb == -1)
		return (0);
	return (1);
}

static char	**assign_elements(t_input *input)
{
	char	**ptr;
	int		r;

	ptr = input->txt;
	r = 0;
	while (ptr && *ptr && !all_assigned(input) && r != -1)
	{
		if (!strncmp(*ptr, "NO", 2))
		{
			// if (input->north) // check if already assigned
			// 	error
			input->north = *ptr + 3;
		}
		else if (!strncmp(*ptr, "SO", 2))
			input->south = *ptr + 3;
		else if (!strncmp(*ptr, "EA", 2))
			input->east = *ptr + 3;
		else if (!strncmp(*ptr, "WE", 2))
			input->west = *ptr + 3;
		else if (!strncmp(*ptr, "F", 1))
			r = assign_color(*ptr + 2, &input->floor);
		else if (!strncmp(*ptr, "C", 1))
			r = assign_color(*ptr + 2, &input->ceiling);
		ptr++;
	}
	if (r == -1 || !all_assigned(input))
		return (NULL);
	return (ptr);
}

static char	**get_input(char *file)
/**
 * "The map must be parsed as it looks [like] in the file." The map meaning the .cub file??
*/
{
	char	**txt;
	int		fd;
	int		rd;
	int		i;

	fd = open(file, O_RDONLY);
	txt = ft_calloc(2, sizeof(char *));
	if (!txt)
		ft_error(NULL);
	rd = get_next_line(txt, fd);
	i = 1;
	while (rd == 1)
	{
		txt = (char **)twod_realloc((void **)txt, 1);
		if (!txt)
		{
			rd = -1;
			break ;
		}
		rd = get_next_line(&txt[i++], fd);
	}
	if (rd < 0)
	{
		if (fd > 0)
			close(fd);
		if (txt)
			txt = (char **)twod_free((void **)txt);
		error_exit(NULL);
	}
	return (txt);
}

void map_parsing(char *filename, t_input *input)
{
	char	**map;

	input->txt = get_input(filename);
	map = assign_elements(input);
	if (!map)
		free_and_exit(".cub: File data invalid or missing.");
	input->map = map_validation(map);
}
