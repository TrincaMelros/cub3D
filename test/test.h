#ifndef TEST_H
 #define TEST_H

#include "cub3d.h"

t_cub3d *g_test;

void	init_test(t_cub3d *cub3d);
void	print_txt(char **print);
void	print_path(t_input input);
void	print_RGB(const t_input input);
void	print_map(t_map map);

#endif