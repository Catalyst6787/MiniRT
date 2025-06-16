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
	return (0);
}

int	test_scalar_division(void)
{
	t_vec3 a = get_vec3(1, -2, 3);

	assert(vec3_isequal(vec3_double_division(a, 2), get_vec3(0.5, -1, 1.5)));
	assert(vec3_isequal(vec3_double_division(a, 2), get_vec3(0.5, -1, 1.5)));
	return (0);
}

int	test_vec_magnitude(void)
{
	t_vec3 v = get_vec3(1, 0, 0);
	double magnitude = vec3_exact_length(&v);
	assert(magnitude == 1);
	v = get_vec3(0, 1, 0);
	magnitude = vec3_exact_length(&v);
	assert(magnitude == 1);
	magnitude = vec3_exact_length(&v);
	assert(magnitude == 1);
	v = get_vec3(1, 2, 3);
	magnitude = vec3_exact_length(&v);
	assert(magnitude == sqrt(14));
	v = get_vec3(-1, -2, -3);
	magnitude = vec3_exact_length(&v);
	assert(magnitude == sqrt(14));
	return (0);
}

int	test_vec_normalize(void)
{
	t_vec3 v;
	v = get_vec3(4, 0, 0);
	v = vec3_normalise(v);
	print_vec3(v, "normalised vector");
	assert(vec3_isequal(v, get_vec3(1, 0, 0)));
	v = get_vec3(1, 2, 3);
	v = vec3_normalise(v);
	assert(vec3_isequal(v, get_vec3(0.26726, 0.53452, 0.80178)));
	return (0);
}

int test_dot_product(void)
{
	t_vec3 a = get_vec3(1, 2, 3);
	t_vec3 b = get_vec3(2, 3, 4);

	assert(vec3_dot(&a, &b) == 20);
	return (0);
}

int test_cross_product(void)
{
	t_vec3 a = get_vec3(1, 2, 3);
	t_vec3 b = get_vec3(2, 3, 4);

	assert(vec3_isequal(vec3_cross(a, b), get_vec3(-1, 2, -1)));
	assert(vec3_isequal(vec3_cross(b, a), get_vec3(1, -2, 1)));
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
	test_scalar_division();
	printf("test_scalar_division passed!\n");
	test_vec_magnitude();
	printf("test_vec_magnitude passed\n");
	test_vec_normalize();
	printf("test_vec_normalize passed\n");
	test_dot_product();
	printf("test_dot_product passed\n");
	test_cross_product();
	printf("test_cross_product passed\n");

	start_all_matrix_tests();
	printf("\nall matrix test passed\n\n");
	start_all_ray_tests();
	printf("\nall ray tests passed\n\n");
	start_all_intersection_tests();
	printf("\nall intersection tests passed\n\n");
	start_all_normals_tests();
	printf("\nall normals tests passed\n\n");
	start_all_reflection_tests();
	printf("\nall reflection tests passed\n\n");
	printf("\n%s", COLOR_RESET);

	return (0);
}
