#include "minirt.h"


void	print_matrice(t_matrix m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m.row)
	{
		j = 0;
		printf("|");
		while (j < m.col)
		{
			printf(" %.1f |", m.matrix[i][j]);
			if (m.matrix[i][j] < 10.0 && m.matrix[i][j] >= 0.0)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

t_matrix	get_matrix(int row, int col, bool identity)
{
	t_matrix	new_matrix;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (row < 1 || row > 4 || col < 1 || col > 4)
		return (print_err(FILE, LINE, "matrix size must be between 1 and 4"),
			get_matrix(4, 4, 0));
	ft_memset(&new_matrix, 0, sizeof(t_matrix));
	new_matrix.row = row;
	new_matrix.col = col;
	if (identity)
	{
		while (i < new_matrix.row)
		{
			while (j < new_matrix.col)
			{
				if (i == j)
					new_matrix.matrix[i][j] = 1;
				j++;
			}
			j = 0;
			i++;
		}
	}
	return (new_matrix);
}

bool	matrix_isequal(t_matrix m1, t_matrix m2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (m1.row != m2.row || m1.col != m2.col)
		return (0);
	while (i < m1.row)
	{
		while (j < m1.col)
		{
			if (!double_isequal(m1.matrix[i][j], m2.matrix[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	matrix_set_elem(t_matrix *m, int i, int j, double elem)
{
	if (i >= m->row || j >= m->col)
	{
		print_err(FILE, LINE, "matrix_set_elem, tried to set element outside of matrix");
		return ;
	}
	m->matrix[i][j] = elem;
}

t_matrix	transpose_matrix(t_matrix m)
{
	int			i;
	int			j;
	t_matrix	res;

	i = 0;
	res = get_matrix(m.col, m.row, 0);
	while (i < res.row)
	{
		j = 0;
		while (j < res.col)
		{
			res.matrix[i][j] = m.matrix[j][i];
			j++;
		}
		i++;
	}
	return (res);
}

