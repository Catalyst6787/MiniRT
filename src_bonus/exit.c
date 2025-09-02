/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:55:44 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:55:45 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_extra(t_scene *scene)
{
	if (scene->objects)
		free(scene->objects);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->buffer)
		free(scene->buffer);
	if (scene->filename)
		free(scene->filename);
	if (scene->lights)
		free(scene->lights);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	if (scene->lights)
		while (++i <= scene->nb_light)
			free(scene->lights[i]);
	i = -1;
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
		mlx_destroy_display(mlx->mlx);
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
	if (ui->str_mode)
		free(ui->str_mode);
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
	exit(0);
}
