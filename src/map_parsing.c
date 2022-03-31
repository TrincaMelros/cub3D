/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/03/31 11:48:48 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_line(const char *line)
/**for map only (...for now)
 * Should probly only check valid info for all file
 * */
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
	return (0);
}

static char	**get_input(char *file)
/**
 * "The map must be parsed as it looks in the file."
 * (Considering just passing text by reference ??
 * Need distinguish syscall error from map validation error
*/
{
	char	**txt;
	// char	**tmp; // consider using char *tmp (1 line)
	int		fd;
	int		rd;
	int		i;

	fd = open(file, O_RDONLY);
	txt = &file; // because effin -Werror
	rd = get_next_line(txt, fd);
	i = 1;
	while (rd == 1)
	{
		txt = (char **)twod_realloc((void **)txt, 1); // assign NULL within function if it doesn't have one already
		if (!txt)
		{
			rd = -1;
			break ;
		}
		// txt = tmp;
		rd = get_next_line(&txt[++i], fd);
		if (parse_line(txt[i]) == -1)
		/*need error message*/
			rd = -1;
	}
	if (rd < 0)
	{
		if (fd > 0)
			close(fd);
		if (txt)
			txt = (char **)twod_free((void **)txt);
		ft_error(NULL);
	}
	return (txt);
}

int map_parsing(char *filename, t_input *input)
{
	input->txt = get_input(filename);
	if (!input->txt)
		return (1);
	if (assign_elements(input) < 0)
		return (1);
	if (!input->map)
		return (1);
	return (0);
}
