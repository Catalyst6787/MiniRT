/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_change_direction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:04 by lfaure            #+#    #+#             */
/*   Updated: 2025/11/18 16:39:51 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_object(t_scene *scene, int keycode, int i)
{
	if (keycode == PAV_UP && scene->objects[i].dir.y <= 0.95)
		scene->objects[i].dir.y += 0.05;
	else if (keycode == PAV_DOWN && scene->objects[i].dir.y >= -0.95)
		scene->objects[i].dir.y -= 0.05;
	else if (keycode == PAV_RIGHT && scene->objects[i].dir.x <= 0.95)
		scene->objects[i].dir.x += 0.05;
	else if (keycode == PAV_LEFT && scene->objects[i].dir.x >= -0.95)
		scene->objects[i].dir.x -= 0.05;
	else if (keycode == PAV_FRONT && scene->objects[i].dir.z <= 0.95)
		scene->objects[i].dir.z += 0.05;
	else if (keycode == PAV_BACK && scene->objects[i].dir.z >= -0.95)
		scene->objects[i].dir.z -= 0.05;
	scene->objects[i].rotation
		= get_rotation_matrix(convert_dir_to_euler
			(vec3_normalise(scene->objects[i].dir)));
	printf("Object rotation : %.2f %.2f %.2f\n",
			scene->objects[i].dir.x,
			scene->objects[i].dir.y,
			scene->objects[i].dir.z);
}

void	change_element_rotation(t_minirt *minirt, t_ui *ui, int keycode, int i)
{
	if (ui->selected_type == OBJ)
	{
		if (minirt->scene->objects[i].type == SPHERE)
			return ;
		handle_object(minirt->scene, keycode, i);
		minirt->scene->objects[i].transform
			= get_object_transformation(&minirt->scene->objects[i]);
		minirt->scene->objects[i].inv
			= get_inversed_matrix(minirt->scene->objects[i].transform);
	}
}
