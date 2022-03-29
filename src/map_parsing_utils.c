/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:15:11 by fbarros           #+#    #+#             */
/*   Updated: 2022/03/29 12:20:24 by fbarros          ###   ########.fr       */
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
	twoD_free((void **)splitter);
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

int	assign_elements(t_input *input)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (input->txt[++i] && !all_assigned(input) && r != -1)
	{
		if (!ft_strncmp(input->txt[i], "NO", 2))
			input->north = input->txt[i] + 3;
		else if (!ft_strncmp(input->txt[i], "SO", 2))
			input->south = input->txt[i] + 3;
		else if (!ft_strncmp(input->txt[i], "EA", 2))
			input->east = input->txt[i] + 3;
		else if (!ft_strncmp(input->txt[i], "WE", 2))
			input->west = input->txt[i] + 3;
		else if (!ft_strncmp(input->txt[i], "F", 1))
			r = assign_color(input->txt[i] + 2, &input->floor);
		else if (!ft_strncmp(input->txt[i], "C", 1))
			r = assign_color(input->txt[i] + 2, &input->ceiling);
	}
	return (r);
}