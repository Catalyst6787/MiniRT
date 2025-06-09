#include "minirt.h"


void	print_matrice(t_matrix *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		printf("|");
		while (j < 4)
		{
			printf(" %.1f |", m->matrix[i][j]);
			if (m->matrix[i][j] < 10.0 && m->matrix[i][j] >= 0.0)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}


void	initialize_matrice(t_matrix *m, bool identity)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (identity && i == j)
				m->matrix[i][j] = 1;
			else
				m->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

t_matrix	get_matrix(int row, int col, bool identity)
{
	t_matrix	new_matrix;
	int			i;
	int			j;

	i = 0;
	j = 0;
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

	if (m1.row != m2.row || m1.col != m2.col)
		return (0);
	while (i < m1.row)
	{
		while (i < m1.col)
		{
			if (m1.matrix[i][j] != m2.matrix[i][j])
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

