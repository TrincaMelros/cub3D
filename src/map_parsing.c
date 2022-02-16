/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:45:21 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/10 16:45:22 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_input_height(char *filename, t_input *input)
{
	int		fd;
	int		size;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd < 1)
		return (1);
	size = 0;
	while (get_next_line(&str, fd))
		size++;
	close(fd);
	input->height = size + 1;
	return (0);
}

static int	get_input(char *filename, t_input *input)
{
	char	*str;
	int		fd;
	int		i;
	int		rd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < input->height)
	{
		rd = get_next_line(&str, fd);
		if (rd == 1)
			input->txt[i] = str;
		else if (rd == 0)
		{
			input->txt[i++] = str;
			break;
		}
		else if (rd == -1)
			return (1);
		i++;	
	}
	input->txt[i] = NULL;
	close(fd);
	return (0);
}

static int assign_texture(t_input *input, int i, char c)
{
	int	j;

	j = 1;
	while (input->txt[i][j] != '.')
		j++;
	if (c == 'N')
		input->north = ft_substr(input->txt[i], j, 20);
	if (c == 'S')
		input->south = ft_substr(input->txt[i], j, 20);
	if (c == 'W')
		input->west = ft_substr(input->txt[i], j, 20);
	if (c == 'E')
		input->east = ft_substr(input->txt[i], j, 20);
	return (0);
}

static int	assign_RGB(t_input *input, int i, char c)
{
	int		j;
	char	**f_splitter;
	char	**c_splitter;

	j = 1;
	while (!ft_isdigit(input->txt[i][j]))
		j++;
	if (c == 'F')
	{
		input->floor_RGB = ft_substr(input->txt[i], j, 20);
		f_splitter = ft_split(input->floor_RGB, ',');
		input->floor_R = ft_atoi(f_splitter[0]);
		input->floor_G = ft_atoi(f_splitter[1]);
		input->floor_B = ft_atoi(f_splitter[2]);
		/**/
		input->floor_TRGB = create_trgb(0, input->floor_R, input->floor_G, input->floor_B);
		/**/
	}
	if (c == 'C')
	{
		input->ceiling_RGB = ft_substr(input->txt[i], j, 20);
		c_splitter = ft_split(input->ceiling_RGB, ',');
		input->ceiling_R = ft_atoi(c_splitter[0]);
		input->ceiling_G = ft_atoi(c_splitter[1]);
		input->ceiling_B = ft_atoi(c_splitter[2]);
		/**/
		input->ceiling_TRGB = create_trgb(0, input->ceiling_R, input->ceiling_G, input->ceiling_B);
		/**/
	}
	return (0);
}

static int	all_assigned(t_input *input)
{
	if (input->north == NULL)
		return (1);
	if (input->south == NULL)
		return (1);
	if (input->west == NULL)
		return (1);
	if (input->east == NULL)
		return (1);
	if (input->floor_RGB == NULL)
		return (1);
	if (input->ceiling_RGB == NULL)
		return (1);
	return (0);
}

static int	assign_elements(t_input *input)
{
	int	i;

	i = -1;
	while(input->txt[++i][0] != '1')
	{
		if (input->txt[i][0] == 'N')
		{
			if (assign_texture(input, i, 'N'))
				return (1);
		}
		else if (input->txt[i][0] == 'S')
		{
			if (assign_texture(input, i, 'S'))
				return (1);
		}
		else if (input->txt[i][0] == 'W')
		{
			if (assign_texture(input, i, 'W'))
				return (1);
		}
		else if (input->txt[i][0] == 'E')
		{
			if (assign_texture(input, i, 'E'))
				return (1);
		}
		else if (input->txt[i][0] == 'F')
		{
			if (assign_RGB(input, i, 'F'))
				return (1);
		}
		else if (input->txt[i][0] == 'C')
		{
			if (assign_RGB(input, i, 'C'))
				return (1);
		}
		if (!all_assigned(input))
			break ;
	}
	return (0);
}

static int	assign_map(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input->txt[i][j] != '1')
		i++;
	input->map = malloc(sizeof(char*) * (input->height - 8 + 1));
	if (!input->map)
		return (1);
	i = 8;
	j = 0;
	while (i < input->height)
	{
		input->map[j] = ft_strdup(input->txt[i]);
		i++;
		j++;
	}
	input->map[j] = NULL;
	return (0);
}

int map_parsing(char *filename, t_input *input)
{
	if (get_input_height(filename, input))
		return (1);
	input->txt = malloc(sizeof(char*) * input->height + 1);
	if (get_input(filename, input))
		return (1);
	if (assign_elements(input))
		return (1);
	if (assign_map(input))
		return (1);
	return (0);
}
