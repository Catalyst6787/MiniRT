#include "minirt.h"

int	debug_print_keycode(int keycode)
{
	ft_printf("keycode: %d\n", keycode);
	return (0);
}

void	debug_aff_image(t_minirt *minirt)
{
	int		x;
	int		y;
	double	red;
	double	green;
	double	blue;

	x = 0;
	y = 0;
	while (y < WIN_H)
	{
		while (x < WIN_W)
		{
			red = (double)x / (WIN_W - 1);
			green = (double)y / (WIN_H - 1);
			blue = 0.0;
			my_mlx_pixel_put(minirt, x, y, ((int)(red * 255) << 16)
				| ((int)(green * 255) << 8) | (int)(blue * 255));
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
}
