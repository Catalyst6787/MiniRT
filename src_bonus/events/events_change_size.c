#include "minirt.h"

static void	handle_object(t_object *object, int keycode)
{
	if (keycode == PAV_UP)
		object->scaling.matrix[1][1] += 0.05;
	else if (keycode == PAV_DOWN && object->scaling.matrix[1][1] >= 0.06)
		object->scaling.matrix[1][1] -= 0.05;
	else if (keycode == PAV_RIGHT)
		object->scaling.matrix[0][0] += 0.05;
	else if (keycode == PAV_LEFT && object->scaling.matrix[0][0] >= 0.06)
		object->scaling.matrix[0][0] -= 0.05;
	else if (keycode == PAV_FRONT)
	{
		object->scaling.matrix[0][0] += 0.05;
		object->scaling.matrix[1][1] += 0.05;
		object->scaling.matrix[2][2] += 0.05;
	}
	else if (keycode == PAV_BACK && object->scaling.matrix[0][0] > 0.05
		&& object->scaling.matrix[1][1] > 0.05
		&& object->scaling.matrix[2][2] > 0.05)
	{
		object->scaling.matrix[0][0] -= 0.05;
		object->scaling.matrix[1][1] -= 0.05;
		object->scaling.matrix[2][2] -= 0.05;
	}
}

void	change_element_size(t_scene *scene, int keycode, int i)
{
	handle_object(&scene->objects[i], keycode);
	scene->objects[i].transform
		= get_object_transformation(&scene->objects[i]);
	scene->objects[i].inv
		= get_inversed_matrix(scene->objects[i].transform);
}
