/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/13 19:21:44 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**line_validation(char *line)
/**
 * if NSEW found return position (but only after parsing through whole line)
 * else if only valid chars found return null
 * else error_and_exit
*/
{
	static char	**ptr;

	while (*line) // do not like this
	/**
	 * repeating myself with constant "if line != NULL" statement
	*/
	{
		while (ft_isspace(*line))
			line++;
		if (*line != '1' && *line != '\0')
			free_and_exit("map: not surrounded by 1's.");
		while (*line && ft_strchr("10NSEW", *line))
		{
			if (*line && ft_strchr("NSEW", *line))
			{
				if (ptr)
					free_and_exit("map: only one position is to be set for player.");
				ptr = (char **)malloc_check(sizeof(char *));
				*ptr = line;
				if (*(++line) && (ft_isspace(*line) || (*line != '1' && *line != '0')))
					free_and_exit("map: player not positioned within map.");
			}
			line++;
		}
		if (*(line - 1) != '1' && *line && !ft_isspace(*line))
			free_and_exit("map: not surrounded by 1's or invalid character in map.");
	}
	return (ptr);
}


static t_map	map_validation(char **map)
/**
 * "Except for the map content, each type of element can be separated by one or more empty lines."
 * NEED CHECK IF "VERTICALLY" VALID
*/
{
	t_map	tmp;
	char **map_start;

	ft_bzero(&tmp, sizeof(tmp));
	while (line_empty(*map))
		map++;
	map_start = map;
	while (map[tmp.h])
	{
		if (ft_strlen(map[tmp.h]) > tmp.w)
			tmp.w = ft_strlen(map[tmp.h]);
		tmp.h++;
	}
	tmp.top_left = ft_calloc(sizeof(t_blocks *), tmp.w * tmp.h);

	unsigned int i = 0;
	while (i < tmp.h)
	{
		if (!init_map_row(tmp.top_left[i], map_start[i]))
		{
			// invalid map char
		}
		i++;
	}
	set_p_pos(&tmp);
	if (invalid_perimeter(&tmp))
	{
		// invalid perimeter
	}
	return (tmp);
}

// static t_map	map_validation(char **map)
// /**
//  * "Except for the map content, each type of element can be separated by one or more empty lines."
//  * NEED CHECK IF "VERTICALLY" VALID
// */
// {
// 	t_map	tmp;
// 	bool	in_map;

// 	in_map = false;
// 	ft_bzero(&tmp, sizeof(tmp));
// 	while (line_empty(*map))
// 		map++;
// 	tmp.top_left = map;
// 	while (map[tmp.h])
// 	{
// 		if (ft_strlen(map[tmp.h]) > tmp.w)
// 			tmp.w = ft_strlen(map[tmp.h]);
// 		if (!in_map || map[tmp.h + 1] == NULL || line_empty(map[tmp.h + 1])) // checking "upper" wall
// 		{
// 			if (ft_strchr(map[tmp.h], '1'))
// 				in_map ^= true;
// 			if (ft_strchr(map[tmp.h], '0'))
// 				free_and_exit("map: not surrounded by 1's.");
// 			if (!in_map)
// 			{
// 				map += tmp.h;
// 				while (line_empty(*map))
// 					map++;
// 				if (map != NULL)
// 					free_and_exit("map: map cannot be separated by empty lines.");	
// 			}
// 		}
// 		tmp.p_pos = line_validation(map[tmp.h++]);
// 		if (!tmp.p_pos)
// 			continue ;
// 		tmp.player_x = ft_strlen(map[tmp.h - 1]) - ft_strlen(*tmp.p_pos);
// 		tmp.player_y = tmp.h - 1;
// 	}
// 	return (tmp);
// }

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
		txt = (char **)twod_realloc((void **)txt, 1); // assign NULL within function if it doesn't have one already
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
