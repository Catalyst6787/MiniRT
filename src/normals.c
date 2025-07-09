#include "minirt.h"

t_vec3	get_sphere_normal_at(const t_object *sp, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;

	object_point = vec3_matrix_multiply(sp->inv, world_point);
	object_normal = vec3_vec_substraction(object_point, get_point3(0, 0, 0));
	world_normal = vec3_matrix_multiply(
			transpose_matrix(sp->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}

t_vec3	get_cylinder_normal_at(const t_object *cy, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;

	object_point = vec3_matrix_multiply(cy->inv, world_point);
	object_normal = get_vec3(object_point.x, 0, object_point.z); // change to (0, 0, 0) if problem
	world_normal = vec3_matrix_multiply(
			transpose_matrix(cy->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}


t_vec3	get_object_normal_at(const t_object *obj, const t_vec3 world_point)
{
	if (obj->type == SPHERE)
		return (get_sphere_normal_at(obj, world_point));
	if (obj->type == PLANE)
		return(obj->obj_data.plane_normal);
	if (obj->type == CYLINDER)
		return (get_cylinder_normal_at(obj, world_point));	
	print_err(FILE, LINE, "get_object_normal : object type not set");
	return (get_vec3(0, 0, 0));
}
