#include "minirt.h"

t_matrix	translate_4x4_matrice(t_matrix *m)
{
	t_matrix	translated_matrix;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			translated_matrix.matrix[i][j] = m->matrix[j][i];
			j++;
		}
		i++;
	}
	return(translated_matrix);
}
