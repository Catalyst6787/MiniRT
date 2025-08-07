#include "minirt.h"

static void	handle_pav_up(t_minirt *minirt, int i)
{
	printf("Object[%d] y++\n", i);
	printf("Objects : %d\n", minirt->scene->nb_objects);
	if (minirt->ui->move_mode == pos)
	{
		if (minirt->scene->nb_objects + minirt->scene->nb_light  == minirt->ui->selected_object)
		{
			if (minirt->scene->ambient->brightness <= 0.9)
			{
				minirt->scene->ambient->brightness += 0.1;
				set_objects_material(minirt->scene);
				create_object_array(minirt->scene);
			}
			return ;
		}
		minirt->scene->objects[i].translation.matrix[1][3] += 0.1;
	}
	else if (minirt->ui->move_mode == dir)
	{
		if (minirt->scene->objects[i].type == SPHERE)
			return ;
		if (minirt->scene->objects[i].dir.y <= 1)
		{
			minirt->scene->objects[i].dir.y += 0.01;
			minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
		}
	}
	else if (minirt->ui->move_mode == size)
	{
		minirt->scene->objects[i].scaling.matrix[0][0] += 0.05; 
		minirt->scene->objects[i].scaling.matrix[1][1] += 0.05; 
		minirt->scene->objects[i].scaling.matrix[2][2] += 0.05; 
	}
	minirt->scene->objects[i].transform = get_object_transformation(&minirt->scene->objects[i]);
}

static void	handle_pav_down(t_minirt *minirt, int i)
{
	printf("Object[%d] y--\n", i);
	if (minirt->ui->move_mode == pos)
	{
		
		if (minirt->scene->nb_objects == minirt->ui->selected_object)
		{
			if (minirt->scene->ambient->brightness >= 0.1)
			{
				minirt->scene->ambient->brightness -= 0.1;
				set_objects_material(minirt->scene);
				create_object_array(minirt->scene);
				return ;
			}
			return ;
		}
		minirt->scene->objects[i].translation.matrix[1][3] -= 0.1;
	}
	else if (minirt->ui->move_mode == dir)
	{
		if (minirt->scene->objects[i].type == SPHERE)
			return ;
		if (minirt->scene->objects[i].dir.y >= -1)
		{
			minirt->scene->objects[i].dir.y -= 0.01;
			minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
		}
	}
	else if (minirt->ui->move_mode == size)
	{
		minirt->scene->objects[i].scaling.matrix[0][0] -= 0.05; 
		minirt->scene->objects[i].scaling.matrix[1][1] -= 0.05; 
		minirt->scene->objects[i].scaling.matrix[2][2] -= 0.05; 
	}
	minirt->scene->objects[i].transform = get_object_transformation(&minirt->scene->objects[i]);
}

static void	handle_pav_left_right(t_minirt *minirt, int i, int keycode)
{
	if (keycode == PAV_LEFT)
	{
		printf("Object[%d] x--\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].translation.matrix[0][3] -= 0.1;
		else if (minirt->ui->move_mode == dir)
		{
			if (minirt->scene->objects[i].type == SPHERE)
				return ;
			if (minirt->scene->objects[i].dir.x >= -1)
			{
				minirt->scene->objects[i].dir.x -= 0.01;
				minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
			}
		}
	}
	else if (keycode == PAV_RIGHT)
	{
		printf("Object[%d] x++\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].translation.matrix[0][3] += 0.1;
		else if (minirt->ui->move_mode == dir)
		{
			if (minirt->scene->objects[i].type == SPHERE)
				return ;
			if (minirt->scene->objects[i].dir.x <= 1)
			{
				minirt->scene->objects[i].dir.x += 0.01;
				minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
			}
		}
	}
	minirt->scene->objects[i].transform = get_object_transformation(&minirt->scene->objects[i]);
}

static void	handle_pav_front_back(t_minirt *minirt, int i, int keycode)
{
	if (keycode == PAV_FRONT)
	{
		printf("Object[%d] z++\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].translation.matrix[2][3] += 0.1;
		else if (minirt->ui->move_mode == dir)
		{
			if (minirt->scene->objects[i].type == SPHERE)
				return ;
			if (minirt->scene->objects[i].dir.z <= 1)
			{
				minirt->scene->objects[i].dir.z += 0.01;
				minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
			}
		}
	}
	else if (keycode == PAV_BACK)
	{
		printf("Object[%d] z--\n", i);
		if (minirt->ui->move_mode == pos)
			minirt->scene->objects[i].translation.matrix[2][3] -= 0.1;
		else if (minirt->ui->move_mode == dir)
		{
			if (minirt->scene->objects[i].type == SPHERE)
				return ;
			if (minirt->scene->objects[i].dir.z >= -1)
			{
				minirt->scene->objects[i].dir.z -= 0.01;
				minirt->scene->objects[i].rotation = get_rotation_matrix(convert_dir_to_euler(minirt->scene->objects[i].dir));
			}
		}
	}
	minirt->scene->objects[i].transform = get_object_transformation(&minirt->scene->objects[i]);
}

void	event_object_position(t_minirt *minirt, int keycode)
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
	if (i != minirt->scene->nb_objects)
		minirt->scene->objects[i].inv
			= get_inversed_matrix(minirt->scene->objects[i].transform);
	start_render(minirt);
}
