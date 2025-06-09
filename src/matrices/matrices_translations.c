#include "minirt.h"

t_matrix	translate_nxn_matrice(t_matrix *m, int n)
{
	t_matrix	translated_matrix;
	int			i;
	int			j;

	if (m->col != m->row)
		return (print_err(FILE, LINE, 
				"Error : trying to translate matrices with i != j"),
				get_matrix(4, 4, 0));
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			translated_matrix.matrix[i][j] = m->matrix[j][i];
			j++;
		}
		i++;
	}
	return(translated_matrix);
}
