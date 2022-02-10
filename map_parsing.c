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

int	get_map_height(char *filename, t_input *x)
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
	x->height = size + 1;
	return (0);
}

int	get_input(char *filename, t_input *x)
{
	char	*str;
	int		fd;
	int		i;
	int		rd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < x->height)
	{
		rd = get_next_line(&str, fd);
		if (rd == 1)
			x->input[i] = str;
		else if (rd == 0)
			break;
		
		
	}
}

int map_parsing(char *filename, t_input *x)
{
	if (get_map_height(filename, x))
		return (1);
	x->input = malloc(sizeof(char*) * x->height + 1);
	if (get_input(filename, x))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_input	x;

    if (argc != 2)
    {
        printf("Error: invalid number of arguments\n");
        return (1);
    }
    if (map_parsing(argv[1], &x))
		return (1);
    return (0);
}