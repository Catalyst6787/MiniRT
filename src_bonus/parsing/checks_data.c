/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:15 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:58:15 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_ok_color(t_vec3 v)
{
	if (v.r < 0 || 255 < v.r)
		return (0);
	if (v.g < 0 || 255 < v.g)
		return (0);
	if (v.b < 0 || 255 < v.b)
		return (0);
	return (1);
}

int	is_ok_dir(t_vec3 v)
{
	if (v.x < -1 || 1 < v.x)
		return (0);
	if (v.y < -1 || 1 < v.y)
		return (0);
	if (v.z < -1 || 1 < v.z)
		return (0);
	return (1);
}

int	is_ok_ratio(double var)
{
	if (var < 0 || 1 < var)
		return (0);
	return (1);
}

static void	check_elements(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	if (!is_ok_ratio(scene->ambient->brightness)
		|| !is_ok_color(scene->ambient->color))
		quit(minirt, WRONG_AMB_DATA);
	if (scene->camera->fov < 0.0 || 180.0 < scene->camera->fov)
		quit(minirt, WRONG_CAM_DATA);
	while (++i < scene->nb_light)
		if (!is_ok_ratio(scene->lights[i]->brightness)
			|| !is_ok_color(scene->lights[i]->color))
			quit(minirt, WRONG_LIGHT_DATA);
}

void	check_data_validity(t_minirt *minirt, t_scene *scene)
{
	int	i;

	check_elements(minirt, scene);
	i = -1;
	while (++i < scene->nb_objects)
		if (!is_ok_color(scene->objects[i].material.color))
			quit(minirt, WRONG_SPH_DATA);
}
