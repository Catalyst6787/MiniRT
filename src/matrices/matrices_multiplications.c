#include "minirt.h"

static double get_dot(t_matrix m1, t_matrix m2, int row, int col)
{
	int i;
	double sum;

	i = 0;
	sum = 0;
	if (row > m1.row || col > m2.col || m1.row != m2.col)
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
