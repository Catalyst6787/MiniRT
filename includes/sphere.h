#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"

typedef struct s_sphere
{
	t_vec3		*pos;
	double		diameter;
	t_vec3		*color;
}	t_sphere;


double		get_sphere_intersection(const t_sphere *sphere, t_ray ray);
t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color);
void		free_sphere(t_sphere *sphere);


#endif
