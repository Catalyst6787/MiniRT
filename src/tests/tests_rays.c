#include "minirt.h"

int	basic_ray_test(void)
{
	t_ray r;

	r = get_ray(get_point3(2, 3, 4), get_vec3(1, 0, 0));
	assert(vec3_isequal(ray_at(0, r), get_point3(2, 3, 4)));
	assert(vec3_isequal(ray_at(1, r), get_point3(3, 3, 4)));
	assert(vec3_isequal(ray_at(-1, r), get_point3(1, 3, 4)));
	assert(vec3_isequal(ray_at(2.5, r), get_point3(4.5, 3, 4)));
	return (0);
}

int	test_ray_intersect_sphere()
{
	t_ray		r;
	t_sphere	s;
	t_vec3		c;
	t_vec3		pos;
	t_inter		inter;

	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	c = get_color(1, 0, 0);
	pos = get_point3(0, 0, 0);
	s.color = &c;
	s.pos = &pos;
	s.diameter = 2;
	inter = get_sphere_inter(&s, r);
	assert(inter.count == 2);
	assert(inter.x[0] == 4.0);
	assert(inter.x[1] == 6.0);
	return (0);
}

int	start_all_ray_tests(void)
{
	basic_ray_test();
	printf("basic_ray_test passed\n");
	test_ray_intersect_sphere();
	printf("test_ray_intersect_sphere passed\n");
	return (0);
}
