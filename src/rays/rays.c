#include "minirt.h"

t_ray	get_ray(t_vec3 org, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = org;
	ray.dir = dir;
	return (ray);
}


t_vec3	ray_at(double t, const t_ray *ray)
{
	t_vec3	v;

	v.x = ray->origin.x + (ray->dir.x * t);
	v.y = ray->origin.y + (ray->dir.y * t);
	v.z = ray->origin.z + (ray->dir.z * t);
	v.w = ray->origin.w;
	return (v);
}

t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray	new_ray;

	new_ray.origin = vec3_matrix_multiply(m, r.origin);
	new_ray.dir = vec3_matrix_multiply(m, r.dir);
	return (new_ray);
}

