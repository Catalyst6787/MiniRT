#include "minirt.h"

int	basic_ray_test(void)
{
	t_ray	r;

	r = get_ray(get_point3(2, 3, 4), get_vec3(1, 0, 0));
	assert(vec3_isequal(ray_at(0, &r), get_point3(2, 3, 4)));
	assert(vec3_isequal(ray_at(1, &r), get_point3(3, 3, 4)));
	assert(vec3_isequal(ray_at(-1, &r), get_point3(1, 3, 4)));
	assert(vec3_isequal(ray_at(2.5, &r), get_point3(4.5, 3, 4)));
	return (0);
}

int	transform_ray_test(void)
{
	t_ray		r;
	t_matrix	m;

	// translating a ray
	r = get_ray(get_point3(1, 2, 3), get_vec3(0, 1, 0));
	m = get_translation_matrix(get_vec3(3, 4, 5));
	r = ray_transform(r, m);
	assert(vec3_isequal(r.origin, get_point3(4, 6, 8)));
	assert(vec3_isequal(r.dir, get_vec3(0, 1, 0)));
	// scaling a ray
	r = get_ray(get_point3(1, 2, 3), get_vec3(0, 1, 0));
	m = get_scaling_matrix(get_vec3(2, 3, 4));
	r = ray_transform(r, m);
	assert(vec3_isequal(r.origin, get_point3(2, 6, 12)));
	assert(vec3_isequal(r.dir, get_vec3(0, 3, 0)));
	return (0);
}

int	start_all_ray_tests(void)
{
	basic_ray_test();
	printf("basic_ray_test passed\n");
	transform_ray_test();
	printf("transform_ray_test passed\n");
	return (0);
}
