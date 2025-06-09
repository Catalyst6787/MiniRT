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
	return (0);
}

