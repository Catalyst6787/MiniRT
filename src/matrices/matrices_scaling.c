#include "minirt.h"

t_matrix	get_scaling_matrice(double x, double y, double z)
{
	t_matrix	m;

	m = get_matrix(4, 4, 0);;
	m.matrix[0][0] = x;
	m.matrix[1][1] = y;
	m.matrix[2][2] = z;
	m.matrix[3][3] = 1;
	return (m);
}
