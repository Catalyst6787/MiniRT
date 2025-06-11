
#include "minirt.h"

int	init_mlx(t_minirt *minirt)
{
	t_img_data	*img_st;
	t_mlx_data	*mlx;

	mlx = minirt->mlx;

	img_st = malloc(sizeof(t_img_data));
	if (!img_st)
		return (perror(MALLOC_ERR), 1);
	ft_memset(img_st, '\0', sizeof(t_img_data));
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "miniRT");
	img_st->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	img_st->addr = mlx_get_data_addr(img_st->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx->img_st = img_st;
	return (0);
}

// int	init_events(t_minirt *minirt)
// {
// 	mlx_hook(minirt->mlx->mlx_win, 2, 1L << 0, handle_keypress, minirt);
// 	mlx_hook(minirt->mlx->mlx_win, 17, 1L << 0, end_mlx_loop, minirt->mlx);
// 	mlx_hook(minirt->mlx->mlx_win, 4, 1L << 2, handle_mouseclick, minirt);
// 	return (0);
// }
