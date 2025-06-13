#include "minirt.h"
#include "vec3.h"

// returns a 4x4 translation matrix built with the given offsets
t_matrix	get_translation_matrix(t_vec3 v)
{
	t_matrix m;

	m = get_matrix(4, 4, 1);
	m.matrix[0][3] = v.x;
	m.matrix[1][3] = v.y;
	m.matrix[2][3] = v.z;
	return (m);
}
