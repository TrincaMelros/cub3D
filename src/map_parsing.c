/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/07 17:24:19 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*line_validation(char *line)
/**
 * if NSEW found return position (but only after parsing through whole line)
 * else if only valid chars found return null
 * else error_and_exit
*/
{
	while (line && *line) // do not like this
	/**
	 * repeating myself with constant "if line != NULL" statement
	*/
	{
		while (line && ft_isspace(*line))
			line++;
		if (line && *line != '1')
			free_and_exit("map: not surrounded by 1's.");
		while (line && (*line == '1' || *line == '0'))
			line++;
		if (line && ft_strchr("NSEW", *line))
			return (line);
		if (line && *(line - 1) != '1')
			free_and_exit("map: not surrounded by 1's");
	}
	return (line);
}

static t_map	map_validation(char **map)
/**
 * "Except for the map content, each type of element can be separated by one or more empty lines."
 * NEED CHECK CLOSURE "VERTICALLY"
*/
{
	t_map	tmp;
	bool	in_map;

	ft_bzero(&tmp, sizeof(tmp));
	tmp.top_left = map;
	while (map[tmp.h])
	{
		if (ft_strlen(map[tmp.h]) > tmp.w) // looking for longest line
			tmp.w = ft_strlen(map[tmp.h]);
		if (!in_map) // checking upper wall
		{
			// skip "whitespace"
			// nothing other than 1's and more whitespace
			if (ft_strchr(map[tmp.h], '1'))
				in_map = true;
			if (ft_strchr(map[tmp.h], '0'))
				free_and_exit("map: not surrounded by 1's.");
		}
		else if(map[tmp.h + 1] == NULL) // last line of map
		{
			// sort of an "inversion" of previous if statement results
		}
		// formula [wht_spc, 1, 0/[N/S/E/W], 1, wht_spc]
		//
		if (in_map && !tmp.p_pos)
		{
			tmp.p_pos = &line_validation(map[tmp.h++]);
			line_validation(*(tmp.p_pos + 1));	// checking through rest of string [REDUNDANT!]
		}
		else if (line_validation(map[tmp.h++])) // if a second instance of NSEW is found
		{
			if (in_map)
				free_and_exit("map: only one position is to be set for player."); // MIGHT JUST NOT BE IN_MAP [!!!!]
//			else if ()
		}
	}
	return (tmp);
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
