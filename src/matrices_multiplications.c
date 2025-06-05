#include "minirt.h"

static double	get_cell(t_matrix m1, t_matrix m2, int row, int col)
{
	double	sum;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sum = 0;
	while (i < m1.cols && j < m2.rows)
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

	if (m1.cols != 4 || m1.rows != 4 || m2.cols != 4 || m2.rows != 4)
		print_err(FILE, LINE, "Wrong 4x4 Matrice Size.\n");
	m3 = new_matrix(get_min_int(m1.rows, m2.rows), 
					get_min_int(m1.cols, m2.cols), 0);
	i = 0;
	while (i < m3.rows)
	{
		j = 0;
		while (j < m3.cols)
		{
			m3.matrix[i][j] = get_cell(m1, m2, i, j);
			j++;
		}
		i++;
	}
	return (m3);
}

