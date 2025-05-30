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

int	test_adding_tuples(void)
{
	t_vec3	a = get_point3(3, -2, 5);
	t_vec3	b = get_vec3(-2, 3, 1);

	assert(vec3_isequal(
			vec3_vec_addition(FILE, LINE, a, b),
			get_point3(1, 1, 6)));

	a = get_vec3(0, 0, 0);
	b = get_vec3(0, 0, 0);
	assert(vec3_isequal(
			vec3_vec_addition(FILE, LINE, a, b),
			get_vec3(0, 0, 0)));
	return (0);
}


// ALL
int	start_all_tests(void)
{
	test_tuple_point();
	test_tuple_vector();
	test_adding_tuples();
	return (0);
}
