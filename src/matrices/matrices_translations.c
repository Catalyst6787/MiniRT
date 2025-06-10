#include "minirt.h"

// returns a 4x4 translation matrix built with the given offsets
t_matrix	get_translation_matrix(double tx, double ty, double tz)
{
	t_matrix m;

	m = get_matrix(4, 4, 1);
	m.matrix[0][3] = tx;
	m.matrix[1][3] = ty;
	m.matrix[2][3] = tz;
	return (m);
}
