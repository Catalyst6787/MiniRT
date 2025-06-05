#include "minirt.h"

typedef	struct s_matrix
{
	int		cols;
	int		rows;
	double	**matrix;
}			t_matrix;

int	get_max_int(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	get_min_int(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}


void	fill_matrice1(double **m1)
{
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[0][3] = 4;
	m1[1][0] = 2;
	m1[1][1] = 4;
	m1[1][2] = 4;
	m1[1][3] = 2;
	m1[2][0] = 8;
	m1[2][1] = 6;
	m1[2][2] = 4;
	m1[2][3] = 1;
	m1[3][0] = 0;
	m1[3][1] = 0;
	m1[3][2] = 0;
	m1[3][3] = 1;
}

void	fill_matrice2(double **m2)
{
	m2[0][0] = 1;
	m2[1][0] = 2;
	m2[2][0] = 3;
	m2[3][0] = 1;
}

void	print_matrice(t_matrix matrice)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrice.rows)
	{
		j = 0;
		while (j < matrice.cols)
		{
			printf("|");
			printf(" %.1f |", matrice.matrix[i][j]);
			if (matrice.matrix[i][j] < 10)
				printf(" ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	free_matrice(t_matrix *matrix)
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
		i++;
	}
	return (new_matrix);
}


double	get_cell(t_matrix m1, t_matrix m2, int row, int col)
{
	double	sum;
	int		i;
	int		j;

	
	i = 0;
	j = 0;
	sum = 0;
	while (i < m1.cols && j < m2.rows)
	{
		
		printf("m1[%d][%d] (%.1f) * m2[%d][%d] (%.1f)", row, j,m1.matrix[row][j], i, col,  m2.matrix[i][col]);
		printf("\n");
		sum += m1.matrix[row][j] * m2.matrix[i][col];
		i++;
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
			printf("\n\n\n");
			j++;
		}
		i++;
	}
	return (m3);
}


// int main ()
// {
// 	// double matrice1[4][4] = {
// 		// 	{1.0, 2.0, 3.0, 4.0},
// 		// 	{2.0, 3.0, 4.0, 5.0},
// 		// 	{3.0, 4.0, 5.0, 6.0},
// 		// 	{4.0, 5.0, 6.0, 7.0}
// 		// };
// 	// double matrice2[4][4] = {
// 	// 	{0.0, 1.0, 2.0, 3.0},
// 	// 	{1.0, 2.0, 4.0, 8.0},
// 	// 	{2.0, 4.0, 8.0, 16.0},
// 	// 	{4.0, 8.0, 16.0, 32.0},
// 	// };
// 	t_matrix	m1 = new_matrix(4, 4);
// 	t_matrix	m2 = new_matrix(4, 1);

	
// 	fill_matrice1(m1.matrix);
// 	fill_matrice2(m2.matrix);
	
// 	t_matrix	m3 = multiply_matrix(m1, m2);
// 	print_matrice(m1);
// 	print_matrice(m2);
// 	print_matrice(m3);
// }