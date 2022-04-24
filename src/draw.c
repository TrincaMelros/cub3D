#include "cub3d.h"

void	draw_rect(t_point coord, const t_point size, int color, t_img *img)
{
	int	i;

	i = coord.x;
	DEBUG(printf("x %d y %d\n", coord.x, coord.y);)
	while (i < coord.x + size.x)
	{
		img_draw_verline(img, i, coord.y, coord.y + size.y - 1, color);
		i++;
	}
}