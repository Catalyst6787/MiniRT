#include "minirt.h"

t_matrix	get_transformation(t_matrix translation,
		t_matrix rotation, t_matrix shearing, t_matrix scaling)
{
	t_matrix	result;

	result = multiply_matrix(translation,
			multiply_matrix(rotation,
				multiply_matrix(
					shearing,
					scaling)));
	return (result);
}

// squishing and shearing not implemented
void	set_sphere_transformation(t_sphere *s)
{
	s->transform = get_transformation(
			get_translation_matrix(s->pos),
			get_matrix(4, 4, 1),
			get_matrix(4, 4, 1),
			get_scaling_matrix(get_vec3(s->radius, s->radius, s->radius)));
	s->inv = get_inversed_matrix(s->transform);
}

// shearing not implemented
void	set_plane_transformation(t_plane *pl)
{
	pl->transform = get_transformation(
			get_translation_matrix(pl->pos),
			get_rotation_matrix(convert_dir_to_euler(pl->dir)),
			get_matrix(4, 4, 1),
			get_matrix(4, 4, 1));
	pl->inv = get_inversed_matrix(pl->transform);
}

t_vec3 convert_dir_to_euler(t_vec3 dir)
{
	t_vec3 euler_angles;
	double len_xz;

	dir = vec3_normalise(dir);
	euler_angles.y = atan2(dir.x, dir.z);
	len_xz = sqrt(dir.x * dir.x + dir.z * dir.z);
	if (len_xz < EPSILON)
	{
		if (dir.y > 0)
			euler_angles.x = M_PI_2;
		else
			euler_angles.x = -M_PI_2;
	}
	else
		euler_angles.x = atan2(dir.y, len_xz);
	euler_angles.z = 0.0;
	return (euler_angles);
}

void	set_cylinder_tranformation(t_cylinder *cy)
{

	debug_print_matrice(get_rotation_matrix(cy->dir), "Rotation");

	cy->transform = get_transformation(
			get_translation_matrix(cy->pos),
			get_rotation_matrix(convert_dir_to_euler(cy->dir)),
			get_matrix(4, 4, 1),
			get_scaling_matrix(get_vec3(cy->radius, cy->height, cy->radius)));
	cy->inv = get_inversed_matrix(cy->transform);
}

