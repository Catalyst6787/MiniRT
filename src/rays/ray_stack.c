#include "minirt.h"


// set_ray_dir and set_ray_pos ?
// copy ray ?


void	set_ray(t_ray *ray, t_vec3 *pos, t_vec3 *dir)
{
	ray->origin = pos;
	ray->dir = dir;
}


t_vec3	ray_at(double t, const t_ray *ray)
{
	t_vec3	v;

	v.x = ray->origin->x + (ray->dir->x * t);
	v.y = ray->origin->y + (ray->dir->y * t);
	v.z = ray->origin->z + (ray->dir->z * t);
	return (v);
}

