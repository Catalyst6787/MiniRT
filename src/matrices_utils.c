#include "minirt.h"

void	print_matrice(t_matrix matrice)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrice.rows)
	{
		j = 0;
		printf("|");
		while (j < matrice.cols)
		{
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

t_matrix	new_matrix(int rows, int cols, bool identity)
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
			if (identity && i == j)
				new_matrix.matrix[i][j] = 1;
			j++;
		}
		i++;
	}
	return (new_matrix);
}

