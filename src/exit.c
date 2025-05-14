/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:22:34 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/14 22:19:31 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// if (DEBUG_MODE)
	// 	ft_putstr_fd("--------------------------\n\n", STDERR_FILENO );
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	if (scene->spheres)
	{
		while (++i < scene->nb_sphere)
		{
			free(scene->spheres[i]->pos);
			free(scene->spheres[i]->color);
			free(scene->spheres[i]);
		}
		free(scene->spheres[i]);
		free(scene->spheres);
	}
	i = -1;
	if (scene->planes)
	{
		while (++i < scene->nb_plane)
		{
			free(scene->planes[i]->dir);
			free(scene->planes[i]->pos);
			free(scene->planes[i]->color);
			free(scene->planes[i]);
		}
		free(scene->planes[i]);
		free(scene->planes);
	}
	i = -1;
	if (scene->cylinders)
	{
		while (++i < scene->nb_cylinder)
		{
			free(scene->cylinders[i]->dir);
			free(scene->cylinders[i]->pos);
			free(scene->cylinders[i]->color);
			free(scene->cylinders[i]);
		}
		free(scene->cylinders[i]);
		free(scene->cylinders);
	}
	if (scene->light)
	{
		free(scene->light->color);
		free(scene->light->pos);
		free(scene->light);
	}
	if (scene->ambient)
	{
		free(scene->ambient->color);
		free(scene->ambient);
	}
	if (scene->camera)
	{
		free(scene->camera->pos);
		free(scene->camera->dir);
		free(scene->camera);
	}
}

int	quit(t_minirt *minirt, char *str)
{
	(void) minirt;
	free_scene(minirt->scene);
	print_exit_info(str);
	mlx_clear_window(minirt->mlx->mlx, minirt->mlx->mlx_win);
	mlx_destroy_image(minirt->mlx->mlx, minirt->mlx->img_st->img);
	minirt->mlx->img_st->addr = NULL;
	mlx_destroy_window(minirt->mlx->mlx, minirt->mlx->mlx_win);
	// mlx_destroy_display(minirt->mlx->mlx);
	free(minirt->mlx->mlx);
	CLOSE_DEBUG_FD;
	exit(0);
}
