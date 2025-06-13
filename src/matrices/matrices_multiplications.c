#include "minirt.h"

static double get_dot(t_matrix m1, t_matrix m2, int row, int col)
{
	int i;
	double sum;

	i = 0;
	sum = 0;
	if (row >= m1.row || col >= m2.col || m1.col != m2.row)
		return (print_err(FILE, LINE, "invalid point outside matrices"), 0);
	while (i < m1.col)
	{
		sum += (m1.matrix[row][i] * m2.matrix[i][col]);
		i++;
	}
	return (sum);
}

t_matrix	mutliply_matrix(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	t_matrix	res;

	i = 0;
	j = 0;
	if (!(m1.col == m2.row))
		return (print_err(FILE, LINE, "matrices have different col and rows"),
			get_matrix(4, 4, 0));
	res = get_matrix(m1.row, m2.col, 0);
	while (i < res.row)
	{
		j = 0;
		while (j < res.col)
		{
			res.matrix[i][j] = get_dot(m1, m2, i, j);
			j++;
		}
		i++;
	}
	return (res);
}

t_vec3	vec3_matrix_multiply(t_matrix m, t_vec3 v)
{
	t_vec3 new;

	new.x = m.matrix[0][0] * v.x + m.matrix[0][1] * v.y + m.matrix[0][2] * v.z + m.matrix[0][3] * v.w;
	new.y = m.matrix[1][0] * v.x + m.matrix[1][1] * v.y + m.matrix[1][2] * v.z + m.matrix[1][3] * v.w;
	new.z = m.matrix[2][0] * v.x + m.matrix[2][1] * v.y + m.matrix[2][2] * v.z + m.matrix[2][3] * v.w;
	new.w = m.matrix[3][0] * v.x + m.matrix[3][1] * v.y + m.matrix[3][2] * v.z + m.matrix[3][3] * v.w;

	return (new);
}
