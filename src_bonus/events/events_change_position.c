#include "minirt.h"

static void	handle_object(t_scene *scene, int keycode, int i)
{
	if (keycode == PAV_UP)
		scene->objects[i].translation.matrix[1][3] += 0.1;
	else if (keycode == PAV_DOWN)
		scene->objects[i].translation.matrix[1][3] -= 0.1;
	else if (keycode == PAV_RIGHT)
		scene->objects[i].translation.matrix[0][3] += 0.1;
	else if (keycode == PAV_LEFT)
		scene->objects[i].translation.matrix[0][3] -= 0.1;
	else if (keycode == PAV_FRONT)
		scene->objects[i].translation.matrix[2][3] += 0.1;
	else if (keycode == PAV_BACK)
		scene->objects[i].translation.matrix[2][3] -= 0.1;
}

static void	handle_lights(t_scene *scene, int keycode, int i)
{
	if (keycode == PAV_UP)
		scene->lights[i]->pos.y += 0.1;
	else if (keycode == PAV_DOWN)
		scene->lights[i]->pos.y -= 0.1;
	else if (keycode == PAV_RIGHT)
		scene->lights[i]->pos.x += 0.1;
	else if (keycode == PAV_LEFT)
		scene->lights[i]->pos.x -= 0.1;
	else if (keycode == PAV_FRONT)
		scene->lights[i]->pos.z += 0.1;
	else if (keycode == PAV_BACK)
		scene->lights[i]->pos.z -= 0.1;
	printf("Light moved\n");
}

static void	handle_ambient(t_scene *scene, int keycode)
{
	if (keycode == PAV_UP && scene->ambient->brightness <= 0.9)
	{
		scene->ambient->brightness += 0.05;
		set_object_ambient_light(scene);
	}
	else if (keycode == PAV_DOWN && scene->ambient->brightness >= 0.1)
	{
		scene->ambient->brightness -= 0.05;
		set_object_ambient_light(scene);
	}
}


void	change_element_position(t_minirt *minirt, t_ui *ui, int keycode, int i)
{
	// int	i;
	(void) ui;

	// i = ui->selected_object;
	if (minirt->ui->selected_type == OBJ)
	{
		handle_object(minirt->scene, keycode, i);
		minirt->scene->objects[i].transform
			= get_object_transformation(&minirt->scene->objects[i]);
		minirt->scene->objects[i].inv
			= get_inversed_matrix(minirt->scene->objects[i].transform);
	}
	else if (minirt->ui->selected_type == LIGHT)
		handle_lights(minirt->scene, keycode, i - minirt->scene->nb_objects);
	else
		handle_ambient(minirt->scene, keycode);
}
