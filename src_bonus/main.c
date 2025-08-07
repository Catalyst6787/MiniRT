#include "minirt.h"

void	init_ui(t_minirt *minirt, t_ui *ui)
{
	ui->str_selected_object = NULL;
	ui->str_mode = ft_strdup("Mode : position");
	if (!ui->str_mode)
		quit(minirt, MALLOC_ERR);
	ui->selected_object = 0;
	ui->command_help = 1;
	ui->move_mode = pos;
	ui->color_id = 0;
	ui->string_color = get_color(1, 1, 1);
}

void	init_render(t_render *render)
{
	render->camera_center.w = 1;
	render->pixel_size = PIXEL_SIZE_MULT;
	render->max_depth = REFLECTION_MAX_DEPTH;
}

void	init_minirt(t_minirt *minirt,
					t_mlx_data *mlx,
					t_scene *scene,
					t_render *render)
{
	t_img_data	img_st;

	ft_memset(minirt, 0, sizeof(t_minirt));
	ft_memset(mlx, 0, sizeof(t_mlx_data));
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(render, 0, sizeof(t_render));
	ft_memset(&img_st, 0, sizeof(t_img_data));
	minirt->mlx = mlx;
	minirt->mlx->img_st = &img_st;
	minirt->scene = scene;
	minirt->render = render;
	init_render(render);
	if (WIN_H < 10 || WIN_W < 10)
		quit(minirt, WIN_SIZE_ERR);
}

int	main(int ac, char **av)
{
	t_minirt	minirt;
	t_mlx_data	mlx;
	t_scene		scene;
	t_render	render;
	t_ui		ui;

	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);
	init_minirt(&minirt, &mlx, &scene, &render);
	minirt.scene->filename = ft_strdup(av[1]);
	if (!minirt.scene->filename)
		quit(&minirt, MALLOC_ERR);
	minirt.ui = &ui;
	init_ui(&minirt, minirt.ui);
	// if (start_all_tests())
	// 	quit(&minirt, TESTS_ERR);
	parse_scene(&minirt);
	init_mlx(&minirt);
	start_render(&minirt);
	printf("%sInitial scene rendered!%s\n\n", GREEN, CRESET);
	mlx_loop(mlx.mlx);
	CLOSE_DEBUG_FD;
	quit(&minirt, "\033[32mQuiting program\n");
	return (0);
}
