
#include "minirt.h"
#include "vec3.h"


t_inter	get_sphere_inter(const t_sphere *sphere, const t_ray ray)
{
	t_vec3	oc;
	t_inter	inter;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	inter = get_inter();
	oc = vec3_vec_substraction(*sphere->pos, ray.origin);
	a = vec3_dot(&ray.dir, &ray.dir);
	b = -2.0 * vec3_dot(&ray.dir, &oc);
	c = vec3_dot(&oc, &oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant > 0)
	{
		inter.x[0] = ((-b - sqrt(discriminant)) / (2.0 * a));
		inter.x[1] = ((-b + sqrt(discriminant)) / (2.0 * a));
		if (double_isequal(inter.x[0], inter.x[1]))
			inter.count = 1;
		else
			inter.count = 2;
	}
	return (inter);
}

// double	hit_sphere(const t_sphere *sphere, const t_ray *ray)
// {
// 	t_vec3	oc;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;

// 	oc = vec3_vec_substraction(*sphere->pos, ray.origin);
// 	a = vec3_dot(&ray.dir, &ray.dir);
// 	b = -2.0 * vec3_dot(&ray.dir, &oc);
// 	c = vec3_dot(&oc, &oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
// 	discriminant = (b * b) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (-1.0);
// 	else
// 	{
// 		return ((-b - sqrt(discriminant)) / (2.0 * a));
// 		// return ((-b + sqrt(discriminant)) / (2.0 * a));
// 	}
// }
