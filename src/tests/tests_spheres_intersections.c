#include "minirt.h"


int test_sphere_intersection(void)
{
	t_sphere	*sphere;
	t_vec3		sphere_pos;
	t_vec3		sphere_col;
	t_ray		ray;

	sphere_pos = get_point3(0, 0, 0);
	sphere_col = get_color(255, 0, 0);
	sphere = new_sphere(sphere_pos, 2, sphere_col);
	ray.origin = get_point3(0, 0, 5);
	ray.dir = get_point3(0, 0, 5);


}