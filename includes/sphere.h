#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"

typedef struct s_sphere
{
	t_vec3		pos;
	t_vec3		color;
	double		diameter;
	double		radius;
	t_matrix	transform;
	t_matrix	inv;
}	t_sphere;


t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color);
void		free_sphere(t_sphere *sphere);

#endif
