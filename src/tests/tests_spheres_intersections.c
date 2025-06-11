#include "minirt.h"


int test_sphere_intersection(void)
{
	t_sphere	*sphere;
	t_vec3		sphere_pos;
	t_vec3		sphere_col;
	t_ray		ray;
	double		inter;
	(void)inter;
	
	sphere_pos = get_point3(0, 0, 0);
	sphere_col = get_color(255, 0, 0);
	sphere = new_sphere(sphere_pos, 2, sphere_col);
	ray.origin = get_point3(0, 0, -5);
	ray.dir = get_vec3(0, 0, 1);
	inter = get_sphere_intersection(sphere, ray);

	free_sphere(sphere);
	return (0);
}


int	start_sphere_tests()
{
	test_sphere_intersection();
	return (0);
}