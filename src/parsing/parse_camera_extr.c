/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_extr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:45:38 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 15:45:40 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

int	parse_camera_extra(t_minirt *minirt, t_scene *scene, int i, int *cursor)
{
	t_vec3	dir;

	dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	dir.w = 0;
	check_direction_vector(minirt, &dir);
	scene->camera->view.to = vec3_vec_addition(scene->camera->view.from,
			vec3_normalise(dir));
	scene->camera->view.up = get_vec3(0, 1, 0);
	scene->camera->hsize = WIN_W;
	scene->camera->vsize = WIN_H;
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n')
		* M_PI / 180;
	return (*cursor = i, 1);
}
