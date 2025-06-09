#include "minirt.h"

static double	get_cell(double m1[4][4], double m2[4][4], int row, int col)
{
	double	sum;
	int		i;

	i = 0;
	sum = 0;
	while (i < 4)
	{
		sum += m1[row][i] * m2[i][col];
		i++;
	}
	return (sum);
}

t_matrix	multiply_4x4_matrix(t_matrix *m1, t_matrix *m2)
{
	int			i;
	int			j;
	t_matrix	m3;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m3.matrix[i][j] = get_cell(m1->matrix, m2->matrix, i, j);
			j++;
		}
		i++;
	}
	return (m3);
}
