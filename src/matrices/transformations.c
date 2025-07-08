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
	pl->transform = multiply_matrix(
			get_translation_matrix(pl->pos),
			get_rotation_matrix(pl->dir));
	pl->inv = get_inversed_matrix(pl->transform);
}

void	set_cylinder_tranformation(t_cylinder *cy)
{
	cy->transform = multiply_matrix(
			get_translation_matrix(cy->pos),
			multiply_matrix(
				get_rotation_matrix(cy->dir),
				get_scaling_matrix(
					get_vec3(
						cy->radius, //replace by radius if implemented
						cy->height,
						cy->radius))));
	cy->inv = get_inversed_matrix(cy->transform);
}

