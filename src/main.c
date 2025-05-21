#include "minirt.h"

void	init_struct(t_mlx_data *mlx, t_img_data *img, t_scene *scene, t_minirt *minirt, t_render *render)
{
	ft_memset(minirt, '\0', sizeof(t_minirt));
	ft_memset(mlx, '\0', sizeof(t_mlx_data));
	ft_memset(img, '\0', sizeof(t_img_data));
	ft_memset(scene, '\0', sizeof(t_scene));
	ft_memset(render, '\0', sizeof(t_render));

	minirt->mlx = mlx;
	minirt->mlx->img_st = img;
	minirt->scene = scene;
	minirt->render = render;
}

int	start_render(t_minirt *minirt)
{
	clock_t	t;
	double	time_taken;
	int		err;

	t = clock();

	err = render_scene(minirt, minirt->mlx, minirt->scene);

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("rendered image in %f seconds\n", time_taken);
	return (err);
}

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_img_data	img;
	t_scene		scene;
	t_minirt	minirt;
	t_render	render;

	init_struct(&mlx, &img, &scene, &minirt, &render);
	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);
	parse_scene(&minirt, av[1]);
	if (WIN_H < 10 || WIN_W < 10)
		quit(&minirt, WIN_SIZE_ERR);
	if (init_structure(&mlx, &img))
		quit(&minirt, MLX_ERR);
	init_events(&mlx);

	start_render(&minirt);

	mlx_loop(mlx.mlx);
	quit(&minirt, "\033[32mQuiting program\n");
	return (0);
}
