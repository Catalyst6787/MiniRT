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

	i = -1;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	while (++i < minirt->scene->nb_objects)
	{
		if (minirt->scene->objects[i].type == CYLINDER)
		{
			if (i % 2)
			{
				minirt->scene->objects[i].transform
					= multiply_matrix(minirt->scene->objects[i].transform,
						get_rotation_matrix(get_vec3(0, 0, 0.1)));
			}
			else
			{
				minirt->scene->objects[i].transform
					= multiply_matrix(minirt->scene->objects[i].transform,
						get_rotation_matrix(get_vec3(0, 0, -0.1)));
			}
			minirt->scene->objects[i].inv
				= get_inversed_matrix(minirt->scene->objects[i].transform);
		}
	}
	render_scene(minirt);
}

static t_shear	get_shear_val(bool pos)
{
	t_shear	shear;
	int		neg;

	shear = get_shear_params();
	if (pos)
		neg = -1;
	else
		neg = 1;
	shear.xy = 0.1 * neg;
	shear.xz = -0.1 * neg;
	shear.yx = -0.2 * neg;
	shear.yz = 0.2 * neg;
	shear.zx = 0;
	shear.zy = 0;
	return (shear);
}

void	event_sphere_shearing(t_minirt *minirt)
{
	int		i;
	t_shear	shear;

	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		if (minirt->scene->objects[i].type == SPHERE)
		{
			shear = get_shear_val(i % 2);
			minirt->scene->objects[i].transform
				= multiply_matrix(minirt->scene->objects[i].transform,
					get_shearing_matrix(shear));
			minirt->scene->objects[i].inv
				= get_inversed_matrix(minirt->scene->objects[i].transform);
		}
		i++;
	}
	render_scene(minirt);
}
