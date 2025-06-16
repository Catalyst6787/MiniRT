#include "minirt.h"



int	basic_test_reflection(void)
{
	t_vec3	v;
	t_vec3	n;
	t_vec3	r;

	v = get_vec3(1, -1, 0);
	n = get_vec3(0, 1, 0);
	r = get_reflection(v, n);
	assert(vec3_isequal(r, get_vec3(1, 1, 0)));
	return (0);
}

int	test_slanted_reflection(void)
{
	t_vec3	v;
	t_vec3	n;
	t_vec3	r;

	v = get_vec3(0, -1, 0);
	n = get_vec3(sqrt(2) / 2, sqrt(2) / 2, 0);
	r = get_reflection(v, n);
	assert(vec3_isequal(r, get_vec3(1, 0, 0)));

	return (0);
}

int	start_all_reflection_tests(void)
{
	basic_test_reflection();
	printf("basic_test_reflection passed\n");
	test_slanted_reflection();
	printf("test_slanted_reflection passed\n");
	return (0);
}
