/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects_material.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:26:45 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:26:45 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_sphere_material(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_sphere)
	{
		scene->spheres[i]->material
			= get_default_material(scene->spheres[i]->color, scene);
		scene->spheres[i]->material.ambient = scene->ambient->brightness;
		scene->spheres[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
}

static void	set_cylinder_material(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_cylinder)
	{
		scene->cylinders[i]->material
			= get_default_material(scene->cylinders[i]->color, scene);
		scene->cylinders[i]->material.ambient = scene->ambient->brightness;
		scene->cylinders[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
}

static void	set_plane_material(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_plane)
	{
		scene->planes[i]->material
			= get_default_material(scene->planes[i]->color, scene);
		scene->planes[i]->material.ambient = scene->ambient->brightness;
		scene->planes[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
}

void	set_objects_material(t_scene *scene)
{
	set_sphere_material(scene);
	set_cylinder_material(scene);
	set_plane_material(scene);
}
