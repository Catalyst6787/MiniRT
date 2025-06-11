
#include "minirt.h"
#include "vec3.h"

double	get_sphere_intersection(const t_sphere *sphere, t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_vec_substraction(*sphere->pos, ray.origin);
	a = vec3_dot(&ray.dir, &ray.dir);
	b = -2.0 * vec3_dot(&ray.dir, &oc);
	c = vec3_dot(&oc, &oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	else
	{
		return ((-b - sqrt(discriminant)) / (2.0 * a));
		// return ((-b + sqrt(discriminant)) / (2.0 * a));
	}
}
