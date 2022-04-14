/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:15:11 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/14 20:41:41 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_blocks	*init_map_row(char *original, size_t lenght)
{
	int			i;
	t_blocks	*new_map;

	i = 0;
	new_map = calloc_check(lenght, sizeof(t_blocks));
	while (i < (int)lenght)
		new_map[i++] = VOID;
	i = -1;
	while (original[++i])
	{
		if (ft_isspace(original[i]))
		{
			if (original[i] == '\t')
				i += 3;
		}
		else if (original[i] == '1')
			new_map[i] = WALL;
		else if (original[i] == '0')
			new_map[i] = SPACE;
		else if (!ft_strchr("NSEW", original[i]))
		{
			free(new_map);
			free_and_exit("map: invalid map char.");
		}
		else
			new_map[i] = PLAYER;
	}
	return (new_map);
}

static void	check_p_pos(t_map *map)
/**
 * Checks player position
 * If none or too many frees everything, outputs error and exits
*/
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map->top_left[++i])
	{
		j = -1;
		while (++j < (int)map->w)
		{
			if (map->top_left[i][j] == PLAYER)
			{
				if (map->player.x != 0 || map->player.y != 0)
					free_and_exit("map: too many positions set for player.");
				map->player.x = (float)j;
				map->player.y = (float)i;
				map->top_left[i][j] = SPACE;
			}
		}
	}
	if (!map->player.x && !map->player.y)
		free_and_exit("map: no position set for player.");
}

static int	invalid_perimeter(t_map *map)
{
	(void)map;
	return (0);
}

t_map	map_validation(char **map)
/**
 * "Except for the map content, each type of element can be separated by one or more empty lines."
*/
{
	t_map	tmp;
	int		i;

	ft_bzero(&tmp, sizeof(tmp));
	while (line_empty(*map))
		map++;
	while (map[tmp.h])
	{
		// essencially truncates horizontally in case there are too many free spaces
		if ((ft_strlen(map[tmp.h]) - ft_strlen(ft_strrchr(map[tmp.h], '1'))) > tmp.w) // maybe put it in a var
			tmp.w = ft_strlen(map[tmp.h]) - ft_strlen(ft_strrchr(map[tmp.h], '1'));
		tmp.h++;
	// check for more empty lines
		if (line_empty(map[tmp.h]))
		{
			i = tmp.h;
			while (map[++i])
			{
				if (!line_empty(map[i]))
					error_exit("map: map should include no empty lines within.");
			}
			break ;
		}
	}
	tmp.top_left = calloc_check(tmp.h + 1, sizeof(t_blocks *));
	i = -1;
	while (++i < (int)tmp.h)
		tmp.top_left[i] = init_map_row(map[i], tmp.w);
	check_p_pos(&tmp);
	tmp.player.dir = map[(int)tmp.player.y][(int)tmp.player.x];
	DEBUG(print_map(tmp);)
	if (invalid_perimeter(&tmp))
		free_and_exit("map: invalid perimeter."); // OR DO IT FROM WITHIN FUNCTION
	return (tmp);
}