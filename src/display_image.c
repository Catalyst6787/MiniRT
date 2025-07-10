#include "minirt.h"

void	display_image(t_minirt *minirt)
{
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	if (minirt->mlx->command_help)
		mlx_string_put(minirt->mlx->mlx, minirt->mlx->mlx_win, 10, 11, color_to_int(get_color(0.7, 0.7, 0.7)), COMMAND_INFO);
	mlx_string_put(minirt->mlx->mlx, minirt->mlx->mlx_win,  WIN_W - (WIN_W / 10), 11, color_to_int(get_color(0.7, 0.7, 0.7)), minirt->mlx->str_selected_object);
	
	
}