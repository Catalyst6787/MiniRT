#include "minirt.h"

static double	get_cell(t_matrix m1, t_matrix m2, int row, int col)
{
	double	sum;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sum = 0;
	while (i < m1.col && j < m2.row)
	{
		sum += m1.matrix[row][j] * m2.matrix[i][col];
		i++;
		j++;
	}
	return (sum);
}

t_matrix	multiply_4x4_matrix(t_matrix m1, t_matrix m2)
{
	t_matrix	m3;
	int			i;
	int			j;

	if (m1.col != 4 || m1.row != 4 || m2.col != 4 || m2.row != 4)
		print_err(FILE, LINE, "Wrong 4x4 Matrice Size.\n");
	m3 = get_matrix(get_min_int(m1.row, m2.row),
					get_min_int(m1.col, m2.col), 0);
	i = 0;
	while (i < m3.row)
	{
		j = 0;
		while (j < m3.col)
		{
			m3.matrix[i][j] = get_cell(m1, m2, i, j);
			j++;
		}
		i++;
	}
	return (m3);
}


