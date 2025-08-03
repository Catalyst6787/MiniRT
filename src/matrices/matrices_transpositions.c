#include "minirt.h"

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
