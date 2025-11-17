/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_change_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:07 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:51:08 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_object(t_object *object, int keycode)
{
	if (keycode == PAV_UP)
		object->translation.matrix[1][3] += 0.1;
	else if (keycode == PAV_DOWN)
		object->translation.matrix[1][3] -= 0.1;
	else if (keycode == PAV_RIGHT)
		object->translation.matrix[0][3] += 0.1;
	else if (keycode == PAV_LEFT)
		object->translation.matrix[0][3] -= 0.1;
	else if (keycode == PAV_FRONT)
		object->translation.matrix[2][3] += 0.1;
	else if (keycode == PAV_BACK)
		object->translation.matrix[2][3] -= 0.1;
}

static void	handle_lights(t_light *light, int keycode)
{
	if (keycode == PAV_UP)
		light->pos.y += 0.1;
	else if (keycode == PAV_DOWN)
		light->pos.y -= 0.1;
	else if (keycode == PAV_RIGHT)
		light->pos.x += 0.1;
	else if (keycode == PAV_LEFT)
		light->pos.x -= 0.1;
	else if (keycode == PAV_FRONT)
		light->pos.z += 0.1;
	else if (keycode == PAV_BACK)
		light->pos.z -= 0.1;
}

void	change_element_position(t_minirt *minirt, t_ui *ui, int keycode, int i)
{
	if (ui->selected_type == OBJ)
	{
		handle_object(&minirt->scene->objects[i], keycode);
		minirt->scene->objects[i].transform
			= get_object_transformation(&minirt->scene->objects[i]);
		minirt->scene->objects[i].inv
			= get_inversed_matrix(minirt->scene->objects[i].transform);
	}
	else if (ui->selected_type == LIGHT)
	{
		i -= minirt->scene->nb_objects;
		handle_lights(minirt->scene->lights[i], keycode);
		printf("Light[%d] : %2f %2f %2f\n", i, minirt->scene->lights[i]->pos.x,
			minirt->scene->lights[i]->pos.y, minirt->scene->lights[i]->pos.z);
	}
}
