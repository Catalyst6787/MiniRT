#include "minirt.h"

void free_matrice(t_matrix *matrix)
{
	int i = 0;
	
	while (i < matrix->rows)
	{
		free(matrix->matrix[i]);
		i++;
	}
	free(matrix->matrix);
}

t_matrix	new_matrix(int rows, int cols)
{
	t_matrix new_matrix;
	int	i;
	int	j;

	new_matrix.rows = rows;
	new_matrix.cols = cols;
	i = 0;
	new_matrix.matrix = (double **)malloc(sizeof(double *) * rows);
	while (i < rows)
	{
		new_matrix.matrix[i] = malloc(sizeof(double) * cols);
		j = 0;
		while (j < cols)
		{
			new_matrix.matrix[i][j] = 0;
			j++;
		}
	}
	return (new_matrix);
}


double	get_cell(t_matrix m1, t_matrix m2, int row, int col)
{
	double	sum;
	int		i;
	int		j;

	i = 0;
	sum = 0;
	while (j < m1.cols && j < m2.rows)
	{
		j = 0;
		while (i < m2.rows && i < m1.cols)
		{
			sum += m1.matrix[row][j] * m2.matrix[i][col];
			i++;
		}
		j++;
	}
	return (sum);
}

t_matrix	multiply_matrix(t_matrix m1, t_matrix m2)
{
	t_matrix	m3;
	int			i;
	int			j;


	m3 = new_matrix(get_min_int(m1.rows, m2.rows), 
					get_min_int(m1.cols, m2.cols));
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


