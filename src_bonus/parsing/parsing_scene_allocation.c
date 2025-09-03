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

void	alloc_elements(t_minirt *minirt, t_scene *scene)
{
	cam_ambiant_alloc(minirt);
	lights_alloc(minirt, scene);
	objects_alloc(minirt, scene);
}
