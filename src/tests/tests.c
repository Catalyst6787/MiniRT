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

int	test_subtraction_tuples(void)
{
	t_vec3 p1 = get_point3(3, 2, 1);
	t_vec3 p2 = get_point3(5, 6, 7);

	assert(vec3_isequal(vec3_vec_substraction(p1, p2), get_vec3(-2, -4, -6)));

	t_vec3	p = get_point3(3, 2, 1);
	t_vec3	v = get_vec3(5, 6, 7);

	assert(vec3_isequal(vec3_vec_substraction(p, v), get_point3(-2, -4, -6)));

	t_vec3	v1 = get_vec3(3, 2, 1);
	t_vec3	v2 = get_vec3(5, 6, 7);

	assert(vec3_isequal(vec3_vec_substraction(v1, v2), get_vec3(-2, -4, -6)));

	return (0);
}

int	test_revert_vec(void)
{
	t_vec3 a = get_vec3(1, -2, 3);

	assert(vec3_isequal(vec3_reverse(a), get_vec3(-1, 2, -3)));
	return (0);
}

int	test_scalar_multiplication(void)
{
	t_vec3 a = get_vec3(1, -2, 3);
	assert(vec3_isequal(vec3_double_multiplication(a, 3.5), get_vec3(3.5, -7, 10.5)));
	assert(vec3_isequal(vec3_double_multiplication(a, 3), get_vec3(3, -6, 9)));

	t_vec3 b = get_point3(1, -2, 3);
	assert(vec3_isequal(vec3_double_multiplication(b, 0.5), get_point3(0.5, -1, 1.5)));
	return (0);
}

int	test_tuple_division(void)
{
	t_vec3 a = get_vec3(1, -2, 3);

	assert(vec3_isequal(vec3_double_division(a, 2), get_vec3(0.5, -1, 1.5)));
	assert(vec3_isequal(vec3_double_division(a, 2), get_vec3(0.5, -1, 1.5)));
	return (0);
}

// ALL
int	start_all_tests(void)
{
	printf("%s\n", GREEN);
	test_tuple_point();
	printf("test_tuple_point passed!\n");
	test_tuple_vector();
	printf("test_tuple_vec passed!\n");
	test_adding_tuples();
	printf("test_adding_tuples passed!\n");
	test_subtraction_tuples();
	printf("test_subtraction_tuples passed!\n");
	test_revert_vec();
	printf("test_revert_vec passed!\n");
	test_scalar_multiplication();
	printf("test_scalar_multiplication passed!\n");
	test_tuple_division();
	printf("test_tuple_division passed!");
	printf("\n%s", COLOR_RESET);
	return (0);
}
