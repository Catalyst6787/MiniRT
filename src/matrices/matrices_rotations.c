#include "minirt.h"

t_matrix	get_rotation_matrix_x(double r)
{
	t_matrix	rotated_matrix;

	rotated_matrix = get_matrix(4, 4, 1);
	rotated_matrix.matrix[1][1] = cos(r);
	rotated_matrix.matrix[1][2] = sin(r) * (-1);
	rotated_matrix.matrix[2][1] = sin(r);
	rotated_matrix.matrix[2][2] = cos(r);
	return (rotated_matrix);
}

t_matrix	get_rotation_matrix_y(double r)
{
	t_matrix	rotated_matrix;

	rotated_matrix = get_matrix(4, 4, 1);
	rotated_matrix.matrix[0][0] = cos(r);
	rotated_matrix.matrix[0][2] = sin(r);
	rotated_matrix.matrix[2][0] = sin(r) * (-1);
	rotated_matrix.matrix[2][2] = cos(r);
	return (rotated_matrix);
}

t_matrix	get_rotation_matrix_z(double r)
{
	t_matrix	rotated_matrix;

	rotated_matrix = get_matrix(4, 4, 1);
	rotated_matrix.matrix[0][0] = cos(r);
	rotated_matrix.matrix[0][1] = sin(r) * (-1);
	rotated_matrix.matrix[1][0] = sin(r);
	rotated_matrix.matrix[1][1] = cos(r);
	return (rotated_matrix);
}