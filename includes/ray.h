#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_vec3	*origin;
	t_vec3	*dir;
	// t_vec3	*color;
	// double	brightness;
}			t_ray;


void	set_ray(t_ray *ray, t_vec3 *pos, t_vec3 *dir);
t_vec3	ray_at(double t, const t_ray *ray);

#endif
