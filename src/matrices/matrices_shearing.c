#include "minirt.h"

// returns an 0,0,0,0,0,0 set of parameters
t_shear	get_shear_params(void)
{
	t_shear	shear_params;

	ft_memset(&shear_params, 0, sizeof(t_shear));
	return (shear_params);
}

t_matrix	get_shearing_matrix(t_shear	params)
{
	t_matrix	m;

	m = get_matrix(4, 4, 1);

	m.matrix[0][1] = params.xy;
	m.matrix[0][2] = params.xz;
	m.matrix[1][0] = params.yx;
	m.matrix[1][2] = params.yz;
	m.matrix[2][0] = params.zx;
	m.matrix[2][1] = params.zy;

	return (m);
}
