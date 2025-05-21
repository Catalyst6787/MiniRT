#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"

typedef struct s_sphere
{
	t_vec3		*pos;
	double		diameter;
	t_vec3		*color;
}	t_sphere;


int			hit_sphere(const t_sphere *sphere, const t_ray *ray);
t_sphere	*new_sphere(t_vec3 *pos, double diameter, t_vec3 *color);
void		free_sphere(t_sphere *sphere);


#endif