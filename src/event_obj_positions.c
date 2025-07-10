#include "minirt.h"


// TMaybe to make this work, the rotation matrix must be placed before the scaling matrix
void	event_obj_pos(t_minirt *minirt, int keycode)
{
	int	i;

	i = minirt->mlx->selected_object;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == PAV_UP)
	{
		printf("Object[%d] y++\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0.1, 0)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, 0.1, 0)));
	}
	else if (keycode == PAV_DOWN)
	{
		printf("Object[%d] y--\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, -0.1, 0)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, -0.1, 0)));
	}
	else if (keycode == PAV_LEFT)
	{
		printf("Object[%d] x--\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(-0.1, 0, 0)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(-0.1, 0, 0)));
	}
	else if (keycode == PAV_RIGHT)
	{
		printf("Object[%d] x++\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0.1, 0, 0)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0.1, 0, 0)));
	}
	else if (keycode == PAV_FRONT)
	{
		printf("Object[%d] z++\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0, 0.1)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, 0, 0.1)));
	}
	else if (keycode == PAV_BACK)
	{
		printf("Object[%d] z--\n", i);
		if (minirt->mlx->move_mode == pos)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_translation_matrix(get_vec3(0, 0, -0.1)));
		else if (minirt->mlx->move_mode == dir)
			minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, 0, -0.1)));
	}
	minirt->scene->objects[i].inv = get_inversed_matrix(minirt->scene->objects[i].transform);
	render_scene(minirt);
}