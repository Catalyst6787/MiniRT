#include "minirt.h"



// Tuples tests

int	test_tuple_point(void)
{
	t_vec3	a;

	a = get_point3(4.3, -4.2, 3.1);
	assert(a.x == 4.3);
	assert(a.y == -4.2);
	assert(a.z == 3.1);
	assert(a.w == 1);
	return (0);
}

int	test_tuple_vector(void)
{
	t_vec3	a;

	a = get_vec3(4.3, -4.2, 3.1);
	assert(a.x == 4.3);
	assert(a.y == -4.2);
	assert(a.z == 3.1);
	assert(a.w == 0);
	return (0);
}

// ALL
int	start_all_tests(void)
{
	test_tuple_point();
	test_tuple_vector();
	// test_adding_tuples();
	return (0);
}
