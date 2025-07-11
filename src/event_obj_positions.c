#include "minirt.h"

static void	handle_pav_up(t_minirt *minirt, int i)
{
	printf("Object[%d] y++\n", i);
	if (minirt->ui->move_mode == pos)
		minirt->scene->objects[i].transform
			= multiply_matrix(minirt->scene->objects[i].transform,
				get_translation_matrix(get_vec3(0, 0.1, 0)));
	else if (minirt->ui->move_mode == dir)
		minirt->scene->objects[i].transform
			= multiply_matrix(minirt->scene->objects[i].transform,
				get_rotation_matrix(get_vec3(0, 0.1, 0)));
}

static void	handle_pav_down(t_minirt *minirt, int i)
{
	printf("Object[%d] y--\n", i);
	if (minirt->ui->move_mode == pos)
		minirt->scene->objects[i].transform
			= multiply_matrix(minirt->scene->objects[i].transform,
				get_translation_matrix(get_vec3(0, -0.1, 0)));
	else if (minirt->ui->move_mode == dir)
		minirt->scene->objects[i].transform
			= multiply_matrix(minirt->scene->objects[i].transform,
				get_rotation_matrix(get_vec3(0, -0.1, 0)));
}

static void	handle_pav_left_right(t_minirt *minirt, int i, int keycode)
{
	if (keycode == PAV_LEFT)
	{
		printf("Object[%d] x--\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_translation_matrix(get_vec3(-0.1, 0, 0)));
		else if (minirt->ui->move_mode == dir)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_rotation_matrix(get_vec3(-0.1, 0, 0)));
	}
	else if (keycode == PAV_RIGHT)
	{
		printf("Object[%d] x++\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_translation_matrix(get_vec3(0.1, 0, 0)));
		else if (minirt->ui->move_mode == dir)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_rotation_matrix(get_vec3(0.1, 0, 0)));
	}
}

static void	handle_pav_front_back(t_minirt *minirt, int i, int keycode)
{
	if (keycode == PAV_FRONT)
	{
		printf("Object[%d] z++\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_translation_matrix(get_vec3(0, 0, 0.1)));
		else if (minirt->ui->move_mode == dir)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_rotation_matrix(get_vec3(0, 0, 0.1)));
	}
	else if (keycode == PAV_BACK)
	{
		printf("Object[%d] z--\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_translation_matrix(get_vec3(0, 0, -0.1)));
		else if (minirt->ui->move_mode == dir)
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_rotation_matrix(get_vec3(0, 0, -0.1)));
	}
}

// Maybe to make this work, the rotation matrix must be placed before the scaling matrix
void	event_obj_pos(t_minirt *minirt, int keycode)
{
	int	i;

	i = minirt->ui->selected_object;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == PAV_UP)
		handle_pav_up(minirt, i);
	else if (keycode == PAV_DOWN)
		handle_pav_down(minirt, i);
	else if (keycode == PAV_LEFT || keycode == PAV_RIGHT)
		handle_pav_left_right(minirt, i, keycode);
	else if (keycode == PAV_FRONT || keycode == PAV_BACK)
		handle_pav_front_back(minirt, i, keycode);
	minirt->scene->objects[i].inv
		= get_inversed_matrix(minirt->scene->objects[i].transform);
	render_scene(minirt);
}
