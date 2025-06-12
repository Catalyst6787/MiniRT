#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"
# include "render.h"

typedef struct s_sphere
{
	t_vec3		pos;
	double		diameter;
	double		radius;
	t_vec3		color;
}	t_sphere;


t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color);
void		scale_sphere(t_sphere *sphere, double ratio);
void		free_sphere(t_sphere *sphere);
int			get_sphere_inter(const t_sphere *sphere, const t_ray ray, t_inter_list *list);

#endif
