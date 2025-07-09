#include "minirt.h"

void	event_obj_pos(t_minirt *minirt, int keycode)
{
	int	i;

	i = minirt->mlx->selected_object;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == PAV_UP)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0.1, 0)));
	else if (keycode == PAV_DOWN)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, -0.1, 0)));
	else if (keycode == PAV_LEFT)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(-0.1, 0, 0)));
	else if (keycode == PAV_RIGHT)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0.1, 0, 0)));
	else if (keycode == PAV_FRONT)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0, 0.1)));
	else if (keycode == PAV_BACK)
		minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0, -0.1)));
	minirt->scene->objects[i].inv = get_inversed_matrix(minirt->scene->objects[i].transform);
	render_scene(minirt);
}