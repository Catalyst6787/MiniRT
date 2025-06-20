
#include "libft.h"
#include "minirt.h"

void	print_exit_info(char *str)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd("(strerror[", STDERR_FILENO);
		ft_putnbr_fd(errno, STDERR_FILENO);
		ft_putstr_fd("] : ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
	}
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	if (scene->spheres)
	{
		while (++i < scene->nb_sphere)
			free(scene->spheres[i]);
		free(scene->spheres[i]);
		free(scene->spheres);
	}
	i = -1;
	if (scene->planes)
	{
		while (++i < scene->nb_plane)
			free(scene->planes[i]);
		free(scene->planes[i]);
		free(scene->planes);
	}
	i = -1;
	if (scene->cylinders)
	{
		while (++i < scene->nb_cylinder)
			free(scene->cylinders[i]);
		free(scene->cylinders[i]);
		free(scene->cylinders);
	}
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
	}
	print_exit_info(str);
	CLOSE_DEBUG_FD;
	exit(0);
}
