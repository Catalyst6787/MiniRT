#include "minirt.h"

/**If size of m == 3, n = 2
 */
t_matrix	get_submatrice(t_matrix m, int row, int col)
{
	int				i_sub;
	int				j_sub;
	int				i;
	int				j;
	t_matrix		submatrice;

	i_sub = 0;
	i = 0;
	submatrice = get_matrix(m.row - 1, m.col - 1, 0);
	while (i_sub < submatrice.row)
	{
		if (i == row)
			i++;
		j_sub = 0;
		j = 0;
		while (j_sub < submatrice.col)
		{
			if (j == col)
				j++;
			submatrice.matrix[i_sub][j_sub] = m.matrix[i][j];
			j++;
			j_sub++;
		}
		i++;
		i_sub++;
	}
	return (submatrice);
}

double	get_determinant_of_3x3_matrice(t_matrix m)
{
	double	cofactor1;
	double	cofactor2;
	double	cofactor3;

	if (m.col != 3 || m.row != 3)
		return (print_err(FILE, LINE,
				"Error : wrong size to get 3x3 determinant"),
				get_matrix(4, 4, 0), 0);
	cofactor1 = get_determinant(get_submatrice(m, 0, 0));
	cofactor2 = get_determinant(get_submatrice(m, 0, 1)) * -1;
	cofactor3 = get_determinant(get_submatrice(m, 0, 2));
	return (cofactor1 * m.matrix[0][0]
			+ cofactor2 * m.matrix[0][1]
			+ cofactor3 * m.matrix[0][2]);
}

double	get_determinant_of_4x4_matrice(t_matrix m)
{
	double	cofactor1;
	double	cofactor2;
	double	cofactor3;
	double	cofactor4;


	if (m.col != 4 || m.row != 4)
		return (print_err(FILE, LINE,
				"Error : wrong size to get 4x4 determinant"),
				get_matrix(4, 4, 0), 0);
	cofactor1 = get_determinant(get_submatrice(m, 0, 0));
	cofactor2 = get_determinant(get_submatrice(m, 0, 1)) * (-1);
	cofactor3 = get_determinant(get_submatrice(m, 0, 2));
	cofactor4 = get_determinant(get_submatrice(m, 0, 3))* (-1);
	return (cofactor1 * m.matrix[0][0]
		+ cofactor2 * m.matrix[0][1]
		+ cofactor3 * m.matrix[0][2]
		+ cofactor4 * m.matrix[0][3]);
}


double	get_determinant(t_matrix m)
{
	if (m.col == 2 && m.row == 2)
		return (m.matrix[0][0] * m.matrix[1][1] - m.matrix[1][0] * m.matrix[0][1]);
	else if (m.col == 3 && m.row == 3)
		return (get_determinant_of_3x3_matrice(m));
	else if (m.col == 4 && m.row == 4)
		return (get_determinant_of_4x4_matrice(m));
	return (print_err(FILE, LINE,
				"Error : wrong size to get determinant"), 0);
}

bool	matrix_is_invertible(t_matrix m)
{
	if (double_isequal(get_determinant(m), 0))
		return (0);
	return (1);
}

t_matrix	get_inversed_matrix(t_matrix m)
{
	t_matrix	inversed_matrix;
	double		determinant;
	int			i;
	int			j;

	if (!matrix_is_invertible(m))
		return (print_err(FILE, LINE, "non-invertible matrix"), m);
	inversed_matrix = get_matrix(m.row, m.col, 0);
	determinant = get_determinant(m);
	i = 0;
	while (i < m.row)
	{
		j = 0;
		while (j < m.col)
		{
			inversed_matrix.matrix[i][j] = get_determinant(get_submatrice(m, j, i)) / determinant;
			if ((i + j) % 2 == 1)
				inversed_matrix.matrix[i][j] *= (-1);
			j++;
		}
		i++;
	}
	return (inversed_matrix);
}
