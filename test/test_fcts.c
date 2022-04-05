#include "test.h"
// #include "cub3d.h"

void	print_txt(char **print)
{
	int	i;

	i = -1;
	while (print[++i])
		printf("%s\n", print[i]);
}

void	print_path(t_input input)
{
	printf("NO -> %s\nSO -> %s\nWE -> %s\nEA -> %s\n", input.north, input.south, input.west, input.east);
}

void	print_RGB(const t_input input)
{
	printf("floor red is %d\n", input.floor.r);
	printf("floor green is %d\n", input.floor.g);
	printf("floor blue is %d\n", input.floor.b);
	printf("floor trgb is %d\n", input.floor.trgb);
	printf("ceiling red is %d\n", input.ceiling.r);
	printf("ceiling green is %d\n", input.ceiling.g);
	printf("ceiling blue is %d\n", input.ceiling.b);
	printf("ceiling trgb is %d\n", input.ceiling.trgb);
}

void	print_map(t_input input)
{
	int i;

	i = -1;
	while (input.map[++i])
		printf("%s\n", input.map[i]);
}
