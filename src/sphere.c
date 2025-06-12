
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
	oc = vec3_vec_substraction(ray.origin, *sphere->pos);
	a = vec3_dot(&ray.dir, &ray.dir);
	b = 2.0 * vec3_dot(&ray.dir, &oc);
	c = vec3_dot(&oc, &oc) - 1;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (inter);
	inter.x[0] = ((-b - sqrt(discriminant)) / (2.0 * a));
	inter.x[1] = ((-b + sqrt(discriminant)) / (2.0 * a));
	inter.count = 2;
	// if (double_isequal(inter.x[0], inter.x[1])) // uncomment this if you want inter.count to be = 1 when at tangent
	// 	inter.count = 1; 							// (truly one intersection)
	return (inter);
}
