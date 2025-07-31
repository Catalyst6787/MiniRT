#include "minirt.h"

static void	free_extra(t_scene *scene)
{
	if (scene->objects)
		free(scene->objects);
	if (scene->light)
		free(scene->light);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->buffer)
		free(scene->buffer);
	if (scene->filename)
		free(scene->filename);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	if (scene->spheres)
	{
		while (++i <= scene->nb_sphere)
			free(scene->spheres[i]);
		free(scene->spheres);
	}
	i = -1;
	if (scene->planes)
	{
		while (++i <= scene->nb_plane)
			free(scene->planes[i]);
		free(scene->planes);
	}
	i = -1;
	if (scene->cylinders)
	{
		while (++i <= scene->nb_cylinder)
			free(scene->cylinders[i]);
		free(scene->cylinders);
	}
	free_extra(scene);
}

void	free_mlx(t_mlx_data *mlx)
{
	if (mlx && mlx->mlx)
	{
		mlx_clear_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_image(mlx->mlx, mlx->img_st->img);
		mlx->img_st->addr = NULL;
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		#ifndef __APPLE__
		mlx_destroy_display(mlx->mlx);
		#endif
		free(mlx->mlx);
		mlx->mlx = NULL;
		free(mlx->img_st);
		mlx->img_st = NULL;
	}
}

void	free_ui(t_ui *ui)
{
	if (ui->str_selected_object)
		free(ui->str_selected_object);
}

int	quit(t_minirt *minirt, char *str)
{
	(void) minirt;
	if (minirt)
	{
		if (minirt->mlx)
			free_mlx(minirt->mlx);
		if (minirt->scene)
			free_scene(minirt->scene);
		if (minirt->render)
			free_render(minirt->render);
		if (minirt->ui)
			free_ui(minirt->ui);
	}
	print_exit_info(str);
	CLOSE_DEBUG_FD;
	exit(0);
}
