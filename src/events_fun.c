#include "minirt.h"

void	event_activate_cylinder_cap(t_minirt *minirt)
{
	int	i;

	i = 0;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	while (i < minirt->scene->nb_objects)
	{
		if (minirt->scene->objects[i].type == CYLINDER)
		{
			if (minirt->scene->objects[i].obj_data.cylinder.isclosed)
				minirt->scene->objects[i].obj_data.cylinder.isclosed = 0;
			else
				minirt->scene->objects[i].obj_data.cylinder.isclosed = 1;
		}
		i++;
	}
	render_scene(minirt);
}

void	event_turn_cylinders(t_minirt *minirt)
{
	int	i;
	int	pair;

	pair = 0;
	i = 0;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	while (i < minirt->scene->nb_objects)
	{
		if (minirt->scene->objects[i].type == CYLINDER)
		{
			if (pair)
			{
				minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, 0, 0.1)));
				pair = 0;
			}
			else
			{
				minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_rotation_matrix(get_vec3(0, 0, -0.1)));
				pair = 1;
			}
			minirt->scene->objects[i].inv = get_inversed_matrix(minirt->scene->objects[i].transform);
		}
		i++;
	}
	render_scene(minirt);
}

void	event_sphere_shearing(t_minirt *minirt)
{
	int	i;
	int	pair;
	t_shear shear;

	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	pair = 0;
	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		if (minirt->scene->objects[i].type == SPHERE)
		{
			if (pair)
			{
				shear.xy = 0.1;
				shear.xz = -0.1;
				shear.yx = -0.2;
				shear.yz = 0.2;
				shear.zx = 0;
				shear.zy = 0;
				minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_shearing_matrix(shear));
				pair = 0;
			}
			else
			{
				shear.xy = -0.1;
				shear.xz = 0.1;
				shear.yx = 0.2;
				shear.yz = -0.2;
				shear.zx = 0;
				shear.zy = 0;
				minirt->scene->objects[i].transform = multiply_matrix(minirt->scene->objects[i].transform, get_shearing_matrix(shear));
				pair = 1;
			}
			minirt->scene->objects[i].inv = get_inversed_matrix(minirt->scene->objects[i].transform);
		}
		i++;
	}
	render_scene(minirt);
}