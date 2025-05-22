#include "minirt.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_img_data	img;
	t_scene		scene;
	t_minirt	minirt;

	ft_memset(&mlx, '\0', sizeof(t_mlx_data));
	ft_memset(&img, '\0', sizeof(t_img_data));
	ft_memset(&scene, '\0', sizeof(t_scene));
	ft_memset(&minirt, '\0', sizeof(t_minirt));
	minirt.mlx = &mlx;
	minirt.scene = &scene;
	minirt.mlx->img_st = &img;

	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);

	parse_scene(&minirt, av[1]);

	if (WIN_H < 10 || WIN_W < 10)
		quit(&minirt, WIN_SIZE_ERR);
	if (init_structure(&mlx, &img))
		quit(&minirt, MLX_ERR);
	init_events(&mlx);

	clock_t t;
	t = clock();

	render_scene(&minirt);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("rendered image in %f seconds\n", time_taken);
	mlx_loop(mlx.mlx);
	CLOSE_DEBUG_FD;
	quit(&minirt, "\033[32mQuiting program\n");
	return (0);
}
