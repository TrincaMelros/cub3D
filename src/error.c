
#include "cub3d.h"

void	error_general(int errnum, char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	if (errnum == SYSCALL)
		perror(strerror(errno));
	exit(errnum);
}