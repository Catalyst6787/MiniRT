#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_vec3	*origin;
	t_vec3	*dir;
	// t_vec3	*color;
	// double	brightness;
}	t_ray;

t_ray	*ray_default_alloc(void);
t_ray	*ray_new_alloc(t_vec3 *origin, t_vec3 *dir);
int		ray_init(t_ray *ray, t_vec3 *origin, t_vec3 *dir);
t_ray	*ray_dup_alloc(t_ray *to_dup);
t_vec3	*ray_position_at(t_ray *ray, const double t);


#endif
