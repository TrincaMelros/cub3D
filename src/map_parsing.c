/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/04/06 16:38:42 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
 
static char	map_validation(const char **map)
{
	
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
	input->txt = get_input(filename);
	if (assign_elements(input) < 0)
		free_and_exit(get_data(NULL), ".cub: File data invalid or missing.");
	map_validation(input->map);
	return (0);
}
