#include "matrice.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "vec3.h"
#include <assert.h>
#include <math.h>

int	start_all_camera_tests(void)
{
	t_camera c;

	c = get_camera(160, 120, M_PI / 2);
	assert(c.hsize == 160);
	assert(c.vsize == 120);
	assert(c.fov ==  M_PI / 2);
	assert(matrix_isequal(c.transform, get_matrix(4, 4, true)));

	return(0);
}
