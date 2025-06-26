#include "matrice.h"
#include "minirt.h"
#include "vec3.h"

int	main(int ac, char **av)
{
	t_minirt		minirt;
	t_mlx_data	mlx;
	t_img_data	img_st;
	t_scene			scene;
	t_render		render;
	clock_t			t;

	ft_memset(&minirt, 0, sizeof(t_minirt));
	ft_memset(&mlx, 0, sizeof(t_mlx_data));
	ft_memset(&scene, 0, sizeof(t_scene));
	ft_memset(&render, 0, sizeof(t_render));
	ft_memset(&img_st, 0, sizeof(t_img_data));
	minirt.mlx = &mlx;
	minirt.mlx->img_st = &img_st;
	minirt.scene = &scene;
	minirt.render = &render;
	minirt.render->camera_center.w = 1;

	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);
	// if (start_all_tests())
	// 	quit(&minirt, TESTS_ERR);
	parse_scene(&minirt, av[1]);

	if (WIN_H < 10 || WIN_W < 10)
		quit(&minirt, WIN_SIZE_ERR);
	init_mlx(&minirt);
	init_events(&minirt);
	t = clock();

	// t_shear shear;
	// shear = get_shear_params();
	// shear.xy = 1;
	// scene.spheres[0]->transform = get_transformation(
	// 		get_translation_matrix(get_vec3(1, 0, 0)),
	// 		get_rotation_matrix(get_vec3(0, 0, 0)),
	// 		get_shearing_matrix(shear),
	// 		get_scaling_matrix(get_vec3(1, 1, 1)));
	// scene.spheres[0]->inv = get_inversed_matrix(scene.spheres[0]->transform);

	// render_scene(&minirt);
	render_scene(&minirt);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("rendered image in %f seconds\n", time_taken);
	mlx_loop(mlx.mlx);
	CLOSE_DEBUG_FD;
	quit(&minirt, "\033[32mQuiting program\n");
	return (0);
}
