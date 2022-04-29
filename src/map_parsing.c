/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <fbarros@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:15:11 by fbarros           #+#    #+#             */
/*   Updated: 2022/04/25 17:20:49 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map	init_t_map(char **map)
/**
 * Gets max width, height and truncates unnecessary spaces both horizontally and vertically
*/
{
	t_map	tmp;
	size_t	trunc_l;
	int		i;

	ft_bzero(&tmp, sizeof(tmp));
	while (map[tmp.h])
	{
		trunc_l = ft_strlen(map[tmp.h]);
		trunc_l -= ft_strlen(ft_strrchr(map[tmp.h], '1'));
		if (trunc_l + 1 > tmp.w)
			tmp.w = trunc_l + 1;
		tmp.h++;
		if (line_empty(map[tmp.h]))
			break ;
	}
	i = tmp.h;
	while (map[i++])
	{
		if (!line_empty(map[i]))
			free_error_exit("map: map should include no empty lines.");
	}
	return (tmp);
}

static t_blocks	*init_map_row(char *original, size_t lenght)
/**
 * Scans line for validity and translates each element to t_blocks(enum) element
 * Initially, everything is set to 0, which equals VOID and is a bit of a dangerous implementation
*/
{
	int			i;
	t_blocks	*new_map;

	new_map = calloc_check(lenght, sizeof(t_blocks));
	i = -1;
	while (original[++i])
	{
		if (ft_isspace(original[i]))
		{
			if (original[i] == '\t')
				i += 3;
		}
		else if (original[i] == '0')
			new_map[i] = SPACE;
		else if (original[i] == '1')
			new_map[i] = WALL;
		else if (ft_strchr("NSEW", original[i]))
			new_map[i] = PLAYER;
		else
		{
			free(new_map);
			free_error_exit("map: invalid map char.");
		}
	}
	return (new_map);
}

static void	check_p_pos(t_map *map)
/**
 * Checks player position
 * If none or too many are found: frees everything(hopefully), outputs error and exits
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
				{
			//		DEBUG(print_map(get_data(0)->input.map);)
					free_error_exit("map: too many positions set for player.");
				}
				map->player.x = (float)j + 0.5;
				map->player.y = (float)i + 0.5;
				map->top_left[i][j] = SPACE;
			}
		}
	}
	if (!map->player.x && !map->player.y)
		free_error_exit("map: no position set for player.");
}

static bool	invalid_perimeter(t_blocks **map, int width)
/**
 * Checks if map is "fenced" with '1's
*/
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (++j < width)
		{
			if (i == 0 || map[i + 1] == NULL)
			{
				if (map[i][j] != VOID && map[i][j] != WALL)
					return (true);
			}
			else if (map[i][j] == SPACE)
			{
				if (map[i + 1][j] == VOID || map[i - 1] == VOID
					|| map[i][j - 1] == VOID || map[i][j + 1] == VOID
					|| map[i + 1][j + 1] == VOID || map[i + 1][j - 1] == VOID
					|| map[i - 1][j + 1] == VOID || map[i - 1][j - 1] == VOID)
					return (true);
			}
		}
	}
	return (false);
}

t_map	map_validation(char **map)
/**
 * "Except for the map content, each type of element can be separated by one or more empty lines."
*/
{
	t_map	tmp;
	int		i;

	tmp = init_t_map(map);
	tmp.top_left = calloc_check(tmp.h + 1, sizeof(t_blocks *));
	i = -1;
	while (++i < (int)tmp.h)
		tmp.top_left[i] = init_map_row(map[i], tmp.w);
	check_p_pos(&tmp);
	tmp.player.dir = map[(int)tmp.player.y][(int)tmp.player.x];
	if (invalid_perimeter(tmp.top_left, (int)tmp.w))
		free_error_exit("map: invalid perimeter.");
	//DEBUG(print_map(tmp);)
	return (tmp);
}
