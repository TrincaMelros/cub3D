/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/21 15:47:22 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_line(const char *line)
/*for map only (for now)*/
{
	static unsigned char	player_in; // if N, S, E or W found once
	static bool				map_in; // if map reached
	int						i;
	char					s[200];
	
	i = -1;
	ft_memset(s, 0, 200);
	// maybe atribute textures here ??
	if (!ft_strset(line, "NO") || !ft_strset(line, "SO") || !ft_strset(line, "EA")
			|| !ft_strset(line, "WE") || !ft_strset(line, "F") || !ft_strset(line, "C"))
			return (0);
	line = ft_strset(line, "\t ");
	while (ft_strchr("01NSEW\t ", line[++i]))
	{
		if (!map_in)
		{
			if (!ft_strset(line, "\t1 "))
			{
				map_in = true;
				return (0);
			}
			ft_strlcpy(s, "Error\nmap: Not surrounded by 1's.", 200);
			break ;
		}
		// if (line[0] != '1' || ft_strrchr(line, '1'))
	}
	if (!s)
		ft_putendl_fd("Error\nmap: Invalid element.\n", 2);
	return (MAPVAL);
}

static char	**get_input(char *file)
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
	// txt[1] = NULL;
	if (fd < 0 || !txt)
	{
		free(txt);
		return (NULL);
	}
	while (rd == 1)
	{
		if (i >= 0)
		{
			tmp = (char **)twoD_realloc((void **)txt, 1);
			if (!tmp)
			{
				rd = -1;
				break ; // ...
			}
			txt = tmp;
		}
		rd = get_next_line(&txt[++i], fd);
		if (parse_line(txt[i]))
			rd = -1; // need error message
	}
	if (rd < 0)
	{
		twoD_free((void **)txt);
		return (NULL);
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
		return (1); // ... or exit from withing function
	if (assign_elements(input) < 0)
		return (1);
	if (!input->map)
		return (1);
	return (0);
}
