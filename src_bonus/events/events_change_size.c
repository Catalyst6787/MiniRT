#include "minirt.h"

static void	handle_object(t_scene *scene, int keycode, int i)
{
	if (keycode == PAV_UP)
	{
		scene->objects[i].scaling.matrix[0][0] += 0.05; 
		scene->objects[i].scaling.matrix[1][1] += 0.05; 
		scene->objects[i].scaling.matrix[2][2] += 0.05; 
	}
	else if (keycode == PAV_DOWN)
	{
		scene->objects[i].scaling.matrix[0][0] -= 0.05; 
		scene->objects[i].scaling.matrix[1][1] -= 0.05; 
		scene->objects[i].scaling.matrix[2][2] -= 0.05; 
	}
	// else if (keycode == PAV_RIGHT)
	// 	minirt->scene->objects[i].translation.matrix[0][3] += 0.1;
	// else if (keycode == PAV_LEFT)
	// 	minirt->scene->objects[i].translation.matrix[0][3] -= 0.1;
	// else if (keycode == PAV_FRONT)
	// 	minirt->scene->objects[i].translation.matrix[2][3] += 0.1;
	// else if (keycode == PAV_DOWN)
	// 	minirt->scene->objects[i].translation.matrix[2][3] -= 0.1;
}

void	change_element_size(t_minirt *minirt, t_ui *ui, int keycode, int i)
{
	(void) ui;
	// int	i;

	// i = ui->selected_object;
	if (minirt->ui->selected_type == OBJ)
	{
		if (minirt->scene->objects[i].type == PLANE)
			return ;
		handle_object(minirt->scene, keycode, i);
		minirt->scene->objects[i].transform
			= get_object_transformation(&minirt->scene->objects[i]);
		minirt->scene->objects[i].inv
			= get_inversed_matrix(minirt->scene->objects[i].transform);
	}
}
