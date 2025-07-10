#include "minirt.h"

void	display_command_help(t_minirt *minirt, t_mlx_data *mlx)
{
	int	color;
	int	x;
	int	y;

	x = -1;
	y = -1;
	color = color_to_int(minirt->ui->string_color);
	mlx_string_put(mlx->mlx, mlx->mlx_win, WIN_W / 2 - (WIN_W / 25), 18, color, minirt->scene->filename);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 18, color, COMMAND_HELP_1);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 33, color, COMMAND_HELP_2);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 48, color, COMMAND_HELP_3);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 63, color, COMMAND_HELP_4);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 78, color, COMMAND_HELP_5);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 93, color, COMMAND_HELP_6);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 108, color, COMMAND_HELP_7);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 123, color, COMMAND_HELP_8);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 138, color, COMMAND_HELP_9);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 153, color, COMMAND_HELP_10);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 168, color, COMMAND_HELP_11);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 183, color, COMMAND_HELP_12);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, 198, color, COMMAND_HELP_13);
	while (++x < 320)
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, 210, color);
	while (++y < 210)
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, 320, y, color);
}

void	display_image(t_minirt *minirt)
{
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	if (minirt->ui->command_help)
		display_command_help(minirt, minirt->mlx);
	mlx_string_put(minirt->mlx->mlx, minirt->mlx->mlx_win,  WIN_W - 140, 18, color_to_int(minirt->ui->string_color), minirt->ui->str_selected_object);
}
