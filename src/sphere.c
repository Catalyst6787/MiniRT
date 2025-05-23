
#include "minirt.h"
#include "vec3.h"

double	hit_sphere(const t_sphere *sphere, const t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_vec_substraction(*sphere->pos, *ray->origin);
	a = vec3_dot(ray->dir, ray->dir);
	b = -2.0 * vec3_dot(ray->dir, &oc);
	c = vec3_dot(&oc, &oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_sphere	*new_sphere(t_vec3 *pos, double diameter, t_vec3 *color)
{
	t_sphere	*sphere;

	// if (!pos || !color)
	// 	return (ft_printf("new_sphere. Error, passed NULL ptr.\n"), NULL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("new_sphere. Error\n"), NULL);
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}
