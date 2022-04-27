#include "test.h"
// #include "cub3d.h"

void	init_test(t_cub3d *cub3d)
{
	g_test = cub3d;
	// set_signal();
}

void	print_txt(char **print)
{
	int	i;

	i = -1;
	if (!print)
		return ;
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

void	print_block(t_blocks block)
{
	// printf("%d", (int)block);
	printf("\033[0m");
	if (block == VOID)
		printf(".");
	else if (block == WALL)
		printf("1");
	else if (block == SPACE)
		printf("0");
	else
		printf("\033[0;31mX");

}

void	print_map(t_map map)
{
	int i = -1, j = -1;

	if (!map.top_left)
		return ;
	while (++j < (int)map.w)
		printf(".");
	printf("\n");
	while (map.top_left[++i])
	{
		j = -1;
		while(++j < (int)map.w)
		{
			if (i == (int)map.player.y && j == (int)map.player.x)
				printf("\033[0;32m%f", map.player.dir);
			else
				print_block(map.top_left[i][j]);
		}
		printf("\n");

	}
	j = -1;
	while (++j < (int)map.w)
		printf(".");
	printf("\n");
	printf("\nPlayer direction: %f", map.player.dir);
	printf("\nHeight: %u Width: %u\n", map.h, map.w);
}


void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	(void)signal;
	(void)arg; //for now
    printf("Caught segfault at address %p\n", si->si_addr);
    error_exit(0);
}

void	set_signal(void/*  *object */)
{
    struct sigaction sa;

    ft_bzero(&sa, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags   = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
}