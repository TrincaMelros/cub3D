#include "../cub3d.h"

int	main(int argc, char **argv)
{

	t_input	input;
	int		ret;

	if (argc != 2)
	{
		perror("Error: invalid number of arguments.\n");
	}
	ret = map_parsing(argv[1], &input);
	if (ret)
	{
		perror(strerror(errno));
		return (errno);
	}
	
	printf("txt:\n");
	ft_puttxt(input.txt);
	printf("\nmap:\n");
	ft_puttxt(input.map);

	return (0);
}