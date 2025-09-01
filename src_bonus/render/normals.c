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

t_vec3	get_plane_normal_at(const t_object *pl, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;

	object_point = vec3_matrix_multiply(pl->inv, world_point);
	object_normal
		= vec3_vec_substraction(object_point, pl->obj_data.plane_normal);
	world_normal = vec3_matrix_multiply(
			transpose_matrix(pl->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}

t_vec3	get_cylinder_normal_at(const t_object *cy, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;
	double	dist;

	object_point = vec3_matrix_multiply(cy->inv, world_point);
	dist = powf(object_point.x, 2) + powf(object_point.z, 2);
	if (dist < 1 && object_point.y >= (cy->obj_data.cylinder.max - EPSILON))
		object_normal = get_vec3(0, 1, 0);
	else if (dist < 1
		&& object_point.y <= (cy->obj_data.cylinder.min + EPSILON))
		object_normal = get_vec3(0, -1, 0);
	else
		object_normal = get_vec3(object_point.x, 0, object_point.z);
	world_normal
		= vec3_matrix_multiply(transpose_matrix(cy->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}

t_vec3	get_cone_normal_at(const t_object *co, const t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;
	double	dist;
	double	y;

	object_point = vec3_matrix_multiply(co->inv, world_point);
	dist = powf(object_point.x, 2) + powf(object_point.z, 2);
	if (dist < powf(co->obj_data.cylinder.max, 2)
		&& object_point.y >= (co->obj_data.cylinder.max))
		object_normal = get_vec3(0, 1, 0);
	else if (dist < powf(co->obj_data.cylinder.min, 2)
		&& object_point.y <= (co->obj_data.cylinder.min))
		object_normal = get_vec3(0, -1, 0);
	else
	{
		y = sqrtf(dist);
		if (object_point.y > 0)
			y *= (-1);
		object_normal = get_vec3(object_point.x, y, object_point.z);
	}
	world_normal
		= vec3_matrix_multiply(transpose_matrix(co->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}

t_vec3	get_object_normal_at(const t_object *obj, const t_vec3 world_point)
{
	if (obj->type == SPHERE)
		return (get_sphere_normal_at(obj, world_point));
	if (obj->type == PLANE)
		return (obj->obj_data.plane_normal);
	if (obj->type == CYLINDER)
		return (get_cylinder_normal_at(obj, world_point));
	if (obj->type == CONE)
		return (get_cone_normal_at(obj, world_point));
	print_err(__FILE__, LINE, "get_object_normal : object type not set");
	return (get_vec3(0, 0, 0));
}
