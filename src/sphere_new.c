#include "minirt.h"


// double	get_sphere_intersection(const t_sphere *sphere, const t_ray ray)
// {
// 	double	inter;
// 	t_vec3	vector;
// 	(void)vector;

// 	inter = 0;
// 	// printf("")
// 	print_vec3(*sphere->pos, "sph pos");
// 	print_vec3(ray.origin, "ray origin");
// 	vector = vec3_vec_substraction(*sphere->pos, ray.origin);
// 	print_vec3(vector, "vector");


// 	return (inter);
// }

t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("new_sphere. Error\n"), NULL);
	sphere->pos = &pos;
	sphere->diameter = diameter;
	sphere->color = &color;
	return (sphere);
}

