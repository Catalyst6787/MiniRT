#include "minirt.h"

t_vec3	get_sphere_normal_at(const t_object *s, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;

	object_point = vec3_matrix_multiply(s->inv, world_point);
	object_normal = vec3_vec_substraction(object_point, get_point3(0, 0, 0));
	world_normal = vec3_matrix_multiply(
			transpose_matrix(s->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}



t_vec3	get_object_normal_at(const t_object *obj, const t_vec3 world_point)
{
	if (obj->type == SPHERE)
		return (get_sphere_normal_at(obj, world_point));
	if (obj->type == PLANE)
		return(obj->plane_normal);
	return (get_sphere_normal_at(obj, world_point)); //delete!!
}
