
#include "minirt.h"

t_ray	*ray_default_alloc(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (perror("Malloc error in ray_default_constructor()\n"), NULL);
	ray->origin = vec3_default_alloc();
	ray->dir = vec3_default_alloc();
	return (ray);
}

// will not copy origin and dir, use with vec3_dup_alloc to send copy.
t_ray	*ray_new_alloc(t_vec3 *origin, t_vec3 *dir)
{
	t_ray	*ray;

	if (!origin || !dir)
		return (ft_printf("ray_new_alloc. Error, passed NULL ptr.\n"), NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (perror("Malloc error in ray_new_alloc()\n"), NULL);
	ray->origin = origin;
	ray->dir = dir;
	return (ray);
}

// will copy origin and dir
int	ray_init(t_ray *ray, t_vec3 *origin, t_vec3 *dir)
{
	if (!origin || !dir)
		return (ft_printf("ray_init. Error, passed NULL ptr.\n"), 1);
	copy_vec3(ray->origin, origin);
	copy_vec3(ray->dir, dir);
	return (0);
}

t_ray	*ray_dup_alloc(t_ray *to_dup)
{
	t_ray	*ray;

	if (!to_dup)
		return (ft_printf("ray_dup_alloc. Error, passed NULL ptr.\n"), NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (perror("Malloc error in ray_dup_alloc()\n"), NULL);
	ray_init(ray, to_dup->origin, to_dup->dir);
	return (ray);
}
