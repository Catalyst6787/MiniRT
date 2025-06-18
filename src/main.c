#include "minirt.h"

int	main(int ac, char **av)
{
	t_minirt	minirt;
	t_mlx_data	mlx;
	t_scene		scene;
	t_render	render;
	clock_t		t;

	ft_memset(&minirt, 0, sizeof(t_minirt));
	ft_memset(&mlx, 0, sizeof(t_mlx_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	ft_memset(&render, 0, sizeof(t_render));
	minirt.mlx = &mlx;
	minirt.scene = &scene;
	minirt.render = &render;
	minirt.render->camera_center.w = 1;

	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);
	if (start_all_tests())
		quit(&minirt, TESTS_ERR);
	parse_scene(&minirt, av[1]);

	if (WIN_H < 10 || WIN_W < 10)
		quit(&minirt, WIN_SIZE_ERR);
	init_mlx(&minirt);
	init_events(&minirt);
	t = clock();

	// fun:
	// if (minirt.scene->spheres[0]) {
	// minirt.scene->spheres[0]->transform = multiply_matrix(get_translation_matrix(get_vec3(1, 0, -1)), multiply_matrix(get_scaling_matrix(get_vec3(1, 0.5, 1)), get_rotation_matrix(get_vec3(0.3, 0, 0))));
	// minirt.scene->spheres[0]->inv = get_inversed_matrix(minirt.scene->spheres[0]->transform); }
	render_scene(&minirt);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("rendered image in %f seconds\n", time_taken);
	mlx_loop(mlx.mlx);
	CLOSE_DEBUG_FD;
	quit(&minirt, "\033[32mQuiting program\n");
	return (0);
}
