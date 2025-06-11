#include "minirt.h"

// if scaling by -1,-1,-1 you get a reflection.
t_matrix	get_scaling_matrix(double tx, double ty, double tz)
{
	t_matrix m;

	m = get_matrix(4, 4, 1);
	m.matrix[0][0] = tx;
	m.matrix[1][1] = ty;
	m.matrix[2][2] = tz;
	return (m);
}
