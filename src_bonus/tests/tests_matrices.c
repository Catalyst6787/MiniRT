#include "minirt.h"

t_matrix	get_arb_matrix(int row, int col,
		double a0, double a1, double a2, double a3,
		double b0, double b1, double b2, double b3,
		double c0, double c1, double c2, double c3,
		double d0, double d1, double d2, double d3)
{
	t_matrix	m = get_matrix(row, col, 0);

	m.matrix[0][0] = a0;
	m.matrix[0][1] = a1;
	m.matrix[0][2] = a2;
	m.matrix[0][3] = a3;
	m.matrix[1][0] = b0;
	m.matrix[1][1] = b1;
	m.matrix[1][2] = b2;
	m.matrix[1][3] = b3;
	m.matrix[2][0] = c0;
	m.matrix[2][1] = c1;
	m.matrix[2][2] = c2;
	m.matrix[2][3] = c3;
	m.matrix[3][0] = d0;
	m.matrix[3][1] = d1;
	m.matrix[3][2] = d2;
	m.matrix[3][3] = d3;

	return (m);
}

int	test_get_max_int(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	test_get_min_int(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}


int	basic_test_matrix(void)
{
	t_matrix	m;

	// m = get_matrix(4, 4, 0);
	// print_matrice(m);
	// printf("matrice m row[%d] col[%d]\n", m.row, m.col);
	// m = get_matrix(4, 4, 1);
	// print_matrice(m);
	// printf("matrice m row[%d] col[%d]\n", m.row, m.col);
	m = get_arb_matrix(4, 4,
			1, 2, 3, 4,
			5.5, 6.5, 7.5, 8.5,
			9, 10, 11, 12,
			13.5, 14.5, 15.5, 16.5);
	// print_matrice(m);
	// printf("matrice m row[%d] col[%d]\n", m.row, m.col);
	assert(m.matrix[0][0] == 1);
	assert(m.matrix[0][3] == 4);
	assert(m.matrix[1][0] == 5.5);
	assert(m.matrix[1][2] == 7.5);
	assert(m.matrix[2][2] == 11);
	assert(m.matrix[3][0] == 13.5);
	assert(m.matrix[3][2] == 15.5);
	return (0);
}

int	test_matrix_isequal(void)
{
	//same matrix
	assert(matrix_isequal(
			get_arb_matrix(4, 4,
				1, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5),
			get_arb_matrix(4, 4,
				1, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5)));
	// different matrix
	assert(!matrix_isequal(
			get_arb_matrix(4, 4,
				42, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5),
			get_arb_matrix(4, 4,
				1, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5)));
	// different size identical matrix
	assert(!matrix_isequal(
			get_arb_matrix(4, 4,
				1, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5),
			get_arb_matrix(4, 2,
				1, 2, 3, 4,
				5.5, 6.5, 7.5, 8.5,
				9, 10, 11, 12,
				13.5, 14.5, 15.5, 16.5)));
	return (0);
}

int	test_matrix_zero(void)
{
	assert(matrix_isequal(
			get_matrix(4, 4, 0),
			get_arb_matrix(4, 4,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0)));
	assert(matrix_isequal(
			get_matrix(1, 1, 0),
			get_arb_matrix(1, 1,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0)));
	assert(matrix_isequal(
			get_matrix(2, 1, 0),
			get_arb_matrix(2, 1,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0)));
	assert(matrix_isequal(
			get_matrix(2, 3, 0),
			get_arb_matrix(2, 3,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0)));
	return (0);
}

int	test_matrix_size(void)
{
	assert(matrix_isequal(get_arb_matrix(2, 2,
							-3, 5, 0, 0,
							1, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
						get_arb_matrix(2, 2,
							-3, 5, 1, 1,
							1, -2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)));
	return (0);
}

int	test_matrix_multiplication(void)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;

	m1 = get_arb_matrix(4, 4,
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2);
	m2 = get_arb_matrix(4, 4,
			-2, 1, 2, 3,
			3, 2, 1, -1,
			4, 3, 6, 5,
			1, 2, 7, 8);
	m3 = get_arb_matrix(4, 4,
			20, 22, 50, 48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26, 46, 42);
	assert(matrix_isequal(multiply_matrix(m1, m2), m3));
	m1 = get_arb_matrix(2, 3,
			1, 2, 3, 0,
			4, 5, 6, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	m2 = get_arb_matrix(3, 2,
			7, 8, 0, 0,
			9, 10, 0, 0,
			11, 12, 0, 0,
			0, 0, 0, 0);

	m3 = get_arb_matrix(2, 2,
			58, 64, 0, 0,
			139, 154, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	assert(matrix_isequal(multiply_matrix(m1, m2), m3));
	m3 = multiply_matrix(m1, m2);
	assert(m3.row == m1.row && m3.col == m2.col);
	// multiplying matrices by "tuples" (4x1 matrice)
	m1 = get_arb_matrix(4, 4,
			1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1);
	m2 = get_arb_matrix(4, 1,
			1, 0, 0, 0,
			2, 0, 0, 0,
			3, 0, 0, 0,
			1, 0, 0, 0);
	m3 = get_arb_matrix(4, 1,
			18, 0, 0, 0,
			24, 0, 0, 0,
			33, 0, 0, 0,
			1, 0, 0, 0);
	assert(matrix_isequal(multiply_matrix(m1, m2), m3));
	m3 = multiply_matrix(m1, m2);
	assert(m3.row == 4);
	assert(m3.col == 1);
	return (0);
}

int	test_matrix_inversion(void)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;

	// 2 x 2 determinant

	m1 = get_arb_matrix(2, 2,
			1, 5, 0, 0,
			-3, 2, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	assert(get_determinant(m1) == 17);

	// submatrices

	m1 = get_arb_matrix(3, 3,
			1, 5, 0, 0,
			-3, 2, 7, 0,
			0, 6, -3, 0,
			0, 0, 0, 0);
	m2 = get_submatrice(m1, 0, 2);
	m3 = get_arb_matrix(2, 2,
			-3, 2, 0, 0,
			-0, 6, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	assert(matrix_isequal(m2, m3));
	m1 = get_arb_matrix(4, 4,
			-6, 1, 1, 6,
			-8, 5, 8, 6,
			-1, 0, 8, 2,
			-7, 1, -1, 1);
	m2 = get_submatrice(m1, 2, 1);
	m3 = get_arb_matrix(3, 3,
			-6, 1, 6, 0,
			-8, 8, 6, 0,
			-7, -1, 1, 0,
			0, 0, 0, 0);
	assert(matrix_isequal(m2, m3));

	// 3x3 matrice determinant

	m1 = get_arb_matrix(3, 3,
			1, 2, 6, 0,
			-5, 8, -4, 0,
			2, 6, 4, 0,
			0, 0, 0, 0);
	assert(get_determinant(m1) == -196);

	// 4x4 matrice determinant

		// test 1

	m1 = get_arb_matrix(4, 4,
			-2, -8, 3, 5,
			-3, 1, 7, 3,
			1, 2, -9, 6,
			-6, 7, 7, -9);
	assert(get_determinant(m1) == -4071);

		// test 2

	m1 = get_arb_matrix(4, 4,
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6);
	assert(get_determinant(m1) == -2120);

	// Matrice inversion

	m1 = get_arb_matrix(4, 4,
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6);
	assert(matrix_is_invertible(m1));
	m1 = get_arb_matrix(4, 4,
			-4, 2, -2, -3,
			9, 6, 2, 6,
			0, -5, 1, -5,
			0, 0, 0, 0);
	assert(!matrix_is_invertible(m1));
	m1 = get_arb_matrix(4, 4,
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4);
	m2 = get_inversed_matrix(m1);
	m3 = get_arb_matrix(4, 4,
		0.21805, 0.45113, 0.24060, -0.04511,
		-0.80827, -1.45677, -0.44361, 0.52068,
		-0.07895, -0.22368, -0.05263, 0.19737,
		-0.52256, -0.81391, -0.30075, 0.30639);
	assert(matrix_isequal(m2, m3));
	m1 = get_arb_matrix(4, 4,
		8, -5, 9, 2,
		7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0, -9, -4);
	m2 = get_inversed_matrix(m1);
	m3 = get_arb_matrix(4, 4,
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692, 0.12308, 0.02564, 0.03077,
		0.35897, 0.35897, 0.43590, 0.92308,
		-0.69231, -0.69231, -0.76923, -1.92308);
	assert(matrix_isequal(m2, m3));
		m1 = get_arb_matrix(4, 4,
		9, 3, 0, 9,
		-5, -2, -6, -3,
		-4, 9, 6, 4,
		-7, 6, 6, 2);
	m2 = get_inversed_matrix(m1);
	m3 = get_arb_matrix(4, 4,
		-0.04074, -0.07778, 0.14444, -0.22222,
		-0.07778, 0.03333, 0.36667, -0.33333,
		-0.02901, -0.14630, -0.10926, 0.12963,
		0.17778, 0.06667, -0.26667, 0.33333);
	assert(matrix_isequal(m2, m3));
	m1 = get_arb_matrix(4, 4,
			3, -9, 7, 3,
			3, -8, 2, -9,
			-4, 4, 4, 1,
			-6, 5, -1, 1);
	m2 = get_arb_matrix(4, 4,
			8, 2, 2, 2,
			3, -1, 7, 0,
			7, 0, 5, 4,
			6, -2, 0, 5);
	m3 = multiply_matrix(m1, m2);
	assert (matrix_isequal(multiply_matrix(m3, get_inversed_matrix(m2)), m1));
	return (0);
}

int	test_identity_matrix(void)
{
	t_matrix m1;
	t_matrix tuple;
	// multiplying by identity matrix should return original matrix
	m1 = get_arb_matrix(4, 4,
			0, 1, 2, 4,
			1, 2, 4, 8,
			2, 4, 8, 16,
			4, 8, 16, 32);
	assert(matrix_isequal(m1, multiply_matrix(m1, get_matrix(4, 4, 1))));
	//multiplying the identity matrix by a tuple should return tuple
	tuple = get_arb_matrix(4, 1,
			1, 0, 0, 0,
			2, 0, 0, 0,
			3, 0, 0, 0,
			4, 0, 0, 0);
	assert(matrix_isequal(tuple, multiply_matrix(get_matrix(4, 4, 1), tuple)));
	return (0);
}

int test_transpose_matrix(void)
{
	t_matrix m;
	t_matrix transposed;

	m = get_arb_matrix(4, 4,
			0, 9, 3, 0,
			9, 8, 0, 8,
			1, 8, 5, 3,
			0, 0, 5, 8);
	transposed = get_arb_matrix(4, 4,
			0, 9, 1, 0,
			9, 8, 8, 0,
			3, 0, 5, 5,
			0, 8, 3, 8);
	// transposing a 4x4 matrix
	assert(matrix_isequal(transpose_matrix(m), transposed));
	// transposing a identity matrix -> doesnt do anything
	assert(matrix_isequal(transpose_matrix(get_matrix(4, 4, 1)),
			get_matrix(4, 4, 1)));
	// transposing a matrix change its shape
	assert(matrix_isequal(get_matrix(1, 4, 0),
			transpose_matrix(get_matrix(4, 1, 0))));
	return (0);
}

int	test_translation(void)
{
	t_matrix	transform;
	t_vec3		point;
	t_vec3		res;
	t_matrix	inv;
	t_vec3		vector;

	transform = get_translation_matrix(get_vec3(5, -3, 2));
	point = get_point3(-3, 4, 5);
	res = get_point3(2, 1, 7);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), res));

	transform = get_translation_matrix(get_vec3(5, -3, 2));
	inv = get_inversed_matrix(transform);
	res = get_point3(-8, 7, 3);
	assert(vec3_isequal(vec3_matrix_multiply(inv, point), res));

	// translation doesnt affect vectors
	transform = get_translation_matrix(get_vec3(5, -3, 2));
	vector = get_vec3(-3, 4, 5);
	assert(vec3_isequal(vec3_matrix_multiply(transform, vector), vector));
	return (0);
}

int	test_scaling(void)
{
	t_matrix	m1;
	t_vec3		point;
	t_vec3		scaled_point;
	t_vec3		result;
	t_matrix	inverse;
	t_vec3		vector;
	// t_matrix	m2;

	m1 = get_scaling_matrix(get_vec3(2, 3, 4));
	point = get_point3(-4, 6, 8);
	scaled_point = vec3_matrix_multiply(m1, point);
	result = get_point3(-8, 18, 32);
	assert(vec3_isequal(scaled_point, result));
	inverse = get_inversed_matrix(m1);
	vector = get_vec3(-4, 6, 8);
	scaled_point = vec3_matrix_multiply(inverse, vector);
	result = get_vec3(-2, 2, 2);
	assert(vec3_isequal(scaled_point, result));

	return (0);
}

int	test_rotation(void)
{
	t_matrix	rotate_matrix;
	t_vec3		point;
	t_vec3		rotated_point;
	t_vec3		result;
	t_matrix	inversed_matrix;

	point = get_point3(0, 1, 0);
	rotate_matrix = get_rotation_matrix_x(M_PI/4);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3(0, sqrtf(2)/2, sqrtf(2)/2);
	assert(vec3_isequal(rotated_point, result));
	rotate_matrix = get_rotation_matrix_x(M_PI/2);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3(0, 0, 1);
	assert(vec3_isequal(rotated_point, result));

	rotate_matrix = get_rotation_matrix_x(M_PI/4);
	inversed_matrix = get_inversed_matrix(rotate_matrix);
	result = get_point3(0, sqrtf(2)/2, (-1) * sqrtf(2)/2);
	assert(vec3_isequal(vec3_matrix_multiply(inversed_matrix, point), result));


	point = get_point3(0, 0, 1);
	rotate_matrix = get_rotation_matrix_y(M_PI/4);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3(sqrtf(2)/2, 0,  sqrtf(2)/2);
	assert(vec3_isequal(rotated_point, result));
	rotate_matrix = get_rotation_matrix_y(M_PI/2);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3(1, 0, 0);
	assert(vec3_isequal(rotated_point, result));


	point = get_point3(0, 1, 0);
	rotate_matrix = get_rotation_matrix_z(M_PI/4);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3((-1) * sqrtf(2)/2, sqrtf(2)/2, 0);
	assert(vec3_isequal(rotated_point, result));
	rotate_matrix = get_rotation_matrix_z(M_PI/2);
	rotated_point = vec3_matrix_multiply(rotate_matrix, point);
	result = get_point3(-1, 0, 0);
	assert(vec3_isequal(rotated_point, result));

	t_matrix	transform;
	t_matrix	inv;
	// t_vec3		point;
	t_vec3		vec;

	transform = get_scaling_matrix(get_vec3(2, 3, 4));
	point = get_point3(-4, 6, 8);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(-8, 18, 32)));

	vec = get_vec3(-4, 6, 8);
	assert(vec3_isequal(vec3_matrix_multiply(transform, vec), get_vec3(-8, 18, 32)));
	return	(0);

	//Multiplying by the inverse of a scaling matrix
	inv = get_inversed_matrix(transform);
	assert(vec3_isequal(vec3_matrix_multiply(inv, vec), get_vec3(-2, 2, 2)));
	// reflection

	transform = get_scaling_matrix(get_vec3(-1, 1, 1));
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(-2, 3, 4)));

	transform = get_scaling_matrix(get_vec3(-1, -1, -1));
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(-2, -3, -4)));
	return (0);
}

int	test_shearing(void)
{
	t_matrix	transform;
	t_shear		shear_params;
	t_vec3		point;

	shear_params = get_shear_params();
	shear_params.xy = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(5, 3, 4)));

	shear_params.xy = 0;
	shear_params.xz = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(6, 3, 4)));

	shear_params.xz = 0;
	shear_params.yx = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(2, 5, 4)));

	shear_params.yx = 0;
	shear_params.yz = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(2, 7, 4)));

	shear_params.yz = 0;
	shear_params.zx = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(2, 3, 6)));

	shear_params.zx = 0;
	shear_params.zy = 1;
	transform = get_shearing_matrix(shear_params);
	point = get_point3(2, 3, 4);
	assert(vec3_isequal(vec3_matrix_multiply(transform, point), get_point3(2, 3, 7)));

	return (0);
}

int	test_chaining(void)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_vec3		p;

	p = get_point3(1, 0, 1);
	a = get_rotation_matrix_x(M_PI / 2);
	b = get_scaling_matrix(get_vec3(5, 5, 5));
	c = get_translation_matrix(get_vec3(10, 5, 7));

	// apply rotation first
	t_vec3 p2 = vec3_matrix_multiply(a, p);
	assert(vec3_isequal(p2, get_point3(1, -1, 0)));

	// apply scaling
	t_vec3 p3 = vec3_matrix_multiply(b, p2);
	assert(vec3_isequal(p3, get_point3(5, -5, 0)));

	t_vec3 p4 = vec3_matrix_multiply(c, p3);
	assert(vec3_isequal(p4, get_point3(15, 0, 7)));

	// Chained transformations must be applied in reverse order
	// for ex, to do T = C * B * A
	t_matrix	transform = multiply_matrix(c, multiply_matrix(b, a));
	// or:
	// t_matrix	transform = multiply_matrix(multiply_matrix(c, b), a);
	p = vec3_matrix_multiply(transform, p);
	assert(vec3_isequal(p, get_point3(15, 0, 7)));
	return (0);
}

int	start_all_matrix_tests(void)
{
	basic_test_matrix();
	printf("basic matrix test passed\n");
	test_matrix_zero();
	printf("test matrix zero passed\n");
	test_matrix_isequal();
	printf("test matrix isequal passed\n");
	test_matrix_size();
	printf("test_matrix_size passed\n");
	test_matrix_multiplication();
	printf("test_matrix_multiplication passed\n");
	test_identity_matrix();
	printf("test_identity_matrix passed\n");
	test_transpose_matrix();
	printf("test_transpose_matrix passed\n");
	test_matrix_inversion();
	printf("test_matrix_inversion passed\n");
	test_translation();
	printf("test_translation passed\n");
	test_scaling();
	printf("test_scaling passed\n");
	test_rotation();
	printf("test_rotation passed\n");
	test_shearing();
	printf("test_shearing passed\n");
	test_chaining();
	printf("test_chaining passed\n");
	return (0);
}

