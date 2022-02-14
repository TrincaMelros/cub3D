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

int	get_map_height(char *filename, t_input *input)
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

int	get_input(char *filename, t_input *input)
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

int assign_textures(t_input *input)
{
	int	error;

	error = 0;
	if (input->txt[0][0] == 'N' && input->txt[0][1] == 'O')
		input->north = ft_substr(input->txt[0], 3, 200);
	else
		error = 1;
	if (input->txt[1][0] == 'S' && input->txt[1][1] == 'O')
		input->south = ft_substr(input->txt[1], 3, 200);
	else
		error = 1;
	if (input->txt[2][0] == 'W' && input->txt[2][1] == 'E')
		input->west = ft_substr(input->txt[2], 3, 200);
	else
		error = 1;
	if (input->txt[3][0] == 'E' && input->txt[3][1] == 'A')
		input->east = ft_substr(input->txt[3], 3, 200);
	else
		error = 1;
	return (error);
}

int map_parsing(char *filename, t_input *input)
{
	if (get_map_height(filename, input))
		return (1);
	input->txt = malloc(sizeof(char*) * input->height + 1);
	if (get_input(filename, input))
		return (1);
	if (assign_textures(input))
		return (1);
	return (0);
}

void	printer(char **print)
{
	int	i;

	i = 0;
	while (print[i])
	{
		printf("%s\n", print[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_cub3d	x;


    if (argc != 2)
    {
        printf("Error: invalid number of arguments\n");
        return (1);
    }
    if (map_parsing(argv[1], &x.input))
		return (1);
	printer(x.input.txt);
    return (0);
}