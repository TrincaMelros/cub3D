#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return ( t << 24 | r << 16 | g << 8 | b);
}

// void	ft_pixel_put(int *addr, int x, int y, int color);
// {
// 	addr[] = 
// }