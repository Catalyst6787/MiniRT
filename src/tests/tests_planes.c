#include "minirt.h"

// t_vec3	get_normal_plane_at(const t_sphere *s, const t_vec3 world_point)
// {
// 	t_vec3	object_point;
// 	t_vec3	object_normal;
// 	t_vec3	world_normal;

// 	object_point = vec3_matrix_multiply(s->inv, world_point);
// 	object_normal = vec3_vec_substraction(object_point, get_point3(0, 0, 0));
// 	world_normal = vec3_matrix_multiply(
// 			transpose_matrix(s->inv), object_normal);
// 	world_normal.w = 0;
// 	return (vec3_normalise(world_normal));
// }

// void	test_plane()
// {
// 	t_plane	plane;
// 	t_ray	ray;

// 	ray = get_ray(get_point3(0, 10, 0), get_vec3(0, 0, 1));



// }


