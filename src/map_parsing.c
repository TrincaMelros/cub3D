/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/28 15:01:28 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_line(const char *line)
/**for map only (...for now)
 * Should probly only check valid info for all file
*/
{
	// static unsigned char	player_in; // if N, S, E or W found once
	static bool				map_in; // if map reached
	int						i;
	char					s[200];

	ft_memset(s, 0, 200);
	i = ft_strlen(line);
	// maybe atribute textures here ??
	if (ft_strnstr(line, "NO", i) || ft_strnstr(line, "SO", i) || ft_strnstr(line, "EA", i)
			|| ft_strnstr(line, "WE", i) || ft_strnstr(line, "F", i) || ft_strnstr(line, "C", i))
			return (0);
	i = 0;
	while (ft_isspace(line[i + 1]))
		i++;
	if (!line[i])
		return (0);
	while (ft_strchr("01NSEW\t ", line[++i]))
	{
		if (!map_in) // ??
		{
			if (ft_strset(line, "1 	"))
			{
				map_in = true;
				return (0);
			}
			ft_strlcpy(s, "Error\nmap: Not surrounded by 1's.", 200);
			break ;
		}
		// if (line[0] != '1' || ft_strrchr(line, '1'))
	}
	if (!*s)
		return (1);
}

static char	**get_input(char *file)
/**
 * "The map must be parsed as it looks in the file."
 * (Considering just passing text by reference ??0
 *
*/
{
	char	**txt;
	char	**tmp; // for safety ... need alternative
	int		fd;
	int		rd;
	int		i;

	fd = open(file, O_RDONLY);
	rd = 1;
	i = -1;
	txt = ft_calloc(2, sizeof(char *));
	if (fd < 0 || !txt)
	{
		free(txt);
		return (NULL);
	}
	while (rd == 1)
	{
		if (i >= 0)
		{
			tmp = (char **)twoD_realloc((void **)txt, 1); // absolute crap! Pass by reference
			if (!tmp)
				ft_error("malloc: failed to allocate memory.\n");
			txt = tmp;
		}
		rd = get_next_line(&txt[++i], fd);
		if (parse_line(txt[i]))
			rd = -1; // need error message
	}
/* 	scan through all map again */
	if (rd < 0)
	{
		twoD_free((void **)txt);
		return (NULL); // or exit?
	}
	close(fd);
	return (txt);
}

static int	assign_color(char *txt, t_color *color)
{
	int		i;
	char	**splitter;

	i = -1;
	splitter = ft_split(txt, ',');
	while (splitter[++i])
		continue ;
	if (i == 3) // avoiding segfault
	{
		color->R = ft_atoi(splitter[0]);
		color->G = ft_atoi(splitter[1]);
		color->B = ft_atoi(splitter[2]);
		color->TRGB = create_trgb(0, color->R, color->G, color->B);
		i = 0;
	}
	else
		i = -1;
	twoD_free((void **)splitter);
	if (color->R > 255 || color->G > 255 || color->B > 255
				|| color->R < 0 || color->G < 0 || color->B < 0)
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
	if (input->floor.TRGB == -1)
		return (0);
	if (input->ceiling.TRGB == -1)
		return (0);
	return (1);
}

static int	assign_elements(t_input *input)
/**/
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while(input->txt[++i] && !all_assigned(input) && r != -1)
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

int map_parsing(char *filename, t_input *input)
{
	input->txt = get_input(filename);
	if (!input->txt)
		return (1); // in case forgot to exit()? 
	if (assign_elements(input) < 0)
		return (1);
	if (!input->map)
		return (1);
	return (0);
}