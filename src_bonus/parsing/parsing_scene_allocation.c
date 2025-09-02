/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_allocation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:41 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:58:07 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "scene.h"

void	cam_ambiant_alloc(t_minirt *minirt)
{
	minirt->scene->ambient = malloc(sizeof(t_ambient));
	if (!minirt->scene->ambient)
		quit(minirt, MALLOC_ERR);
	minirt->scene->camera = malloc(sizeof(t_camera));
	if (!minirt->scene->camera)
		quit(minirt, MALLOC_ERR);
	ft_memset(minirt->scene->ambient, 0, sizeof(t_ambient));
	ft_memset(minirt->scene->camera, 0, sizeof(t_camera));
}

void	lights_alloc(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	minirt->scene->lights
		= malloc(sizeof(t_light *) * (scene->nb_light + 1));
	if (!scene->lights && scene->nb_light)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_light)
	{
		scene->lights[i] = malloc(sizeof(t_light));
		if (!scene->lights[i])
		{
			while (--i >= 0)
				free(scene->lights[i]);
			quit(minirt, MALLOC_ERR);
		}
	}
	scene->lights[i] = NULL;
}

// void	spheres_alloc(t_minirt *minirt, t_scene *scene)
// {
// 	int	i;

// 	i = -1;
// 	minirt->scene->spheres
// 		= malloc(sizeof(t_sphere *) * (scene->nb_sphere + 1));
// 	if (!scene->spheres && scene->nb_sphere)
// 		quit(minirt, MALLOC_ERR);
// 	while (++i < scene->nb_sphere)
// 	{
// 		scene->spheres[i] = malloc(sizeof(t_sphere));
// 		if (!scene->spheres[i])
// 		{
// 			while (--i >= 0)
// 				free(scene->spheres[i]);
// 			quit(minirt, MALLOC_ERR);
// 		}
// 	}
// 	scene->spheres[i] = NULL;
// }

// void	planes_alloc(t_minirt *minirt, t_scene *scene)
// {
// 	int	i;

// 	i = -1;
// 	scene->planes = malloc(sizeof(t_plane *) * (scene->nb_plane + 1));
// 	if (!scene->planes && scene->nb_plane)
// 		quit(minirt, MALLOC_ERR);
// 	while (++i < scene->nb_plane)
// 	{
// 		scene->planes[i] = malloc(sizeof(t_plane));
// 		if (!scene->planes[i])
// 		{
// 			while (--i >= 0)
// 				free(scene->planes[i]);
// 			quit(minirt, MALLOC_ERR);
// 		}
// 	}
// 	scene->planes[i] = NULL;
// }

// void	cylinders_alloc(t_minirt *minirt, t_scene *scene)
// {
// 	int	i;

// 	i = -1;
// 	scene->cylinders = malloc(sizeof(t_cylinder *) * (scene->nb_cylinder + 1));
// 	if (!scene->cylinders && scene->nb_cylinder)
// 		quit(minirt, MALLOC_ERR);
// 	while (++i < scene->nb_cylinder)
// 	{
// 		scene->cylinders[i] = malloc(sizeof(t_cylinder));
// 		if (!scene->cylinders[i])
// 		{
// 			while (--i >= 0)
// 				free(scene->cylinders[i]);
// 			quit(minirt, MALLOC_ERR);
// 		}
// 	}
// 	scene->cylinders[i] = NULL;
// }

// void	cones_alloc(t_minirt *minirt, t_scene *scene)
// {
// 	int	i;

// 	i = -1;
// 	scene->cones = malloc(sizeof(t_cone *) * (scene->nb_cone + 1));
// 	if (!scene->cones && scene->nb_cone)
// 		quit(minirt, MALLOC_ERR);
// 	while (++i < scene->nb_cone)
// 	{
// 		scene->cones[i] = malloc(sizeof(t_cone));
// 		if (!scene->cones[i])
// 		{
// 			while (--i >= 0)
// 				free(scene->cones[i]);
// 			quit(minirt, MALLOC_ERR);
// 		}
// 	}
// 	scene->cones[i] = NULL;
// }

void	alloc_elements(t_minirt *minirt, t_scene *scene)
{
	cam_ambiant_alloc(minirt);
	lights_alloc(minirt, scene);
	// spheres_alloc(minirt, scene);
	// planes_alloc(minirt, scene);
	// cylinders_alloc(minirt, scene);
	// cones_alloc(minirt, scene);
	objects_alloc(minirt, scene);
}
