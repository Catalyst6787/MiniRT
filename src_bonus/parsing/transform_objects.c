/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:53:07 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:58:04 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	get_object_transformation(t_object *obj)
{
	t_matrix	result;

	result = multiply_matrix(obj->translation,
			multiply_matrix(obj->rotation,
				multiply_matrix(obj->shearing, obj->scaling)));
	return (result);
}

void	set_camera_transformation(t_scene *scene)
{
	set_pixel_size(scene->camera);
	scene->camera->transform = get_orientation_matrix(scene->camera->view);
	scene->camera->inv = get_inversed_matrix(scene->camera->transform);
}
