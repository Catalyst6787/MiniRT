#include "matrice.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "vec3.h"
#include <assert.h>
#include <math.h>

int	start_all_camera_tests(void)
{
	t_camera	c;
	t_ray		r;

	// Constructing a camera
	c = get_camera(160, 120, M_PI / 2);
	assert(c.hsize == 160);
	assert(c.vsize == 120);
	assert(c.fov ==  M_PI / 2);
	assert(matrix_isequal(c.transform, get_matrix(4, 4, true)));

	// The pixel size for a horizontal canvas
	c = get_camera(200, 125, M_PI / 2);
	assert(double_isequal(c.pixel_size, 0.01));

	// The pixel size for a vertical canvas
	c = get_camera(125, 200, M_PI / 2);
	assert(double_isequal(c.pixel_size, 0.01));

	// Constructing a ray through the center of the canvas
	c = get_camera(201, 101, M_PI / 2);
	r = ray_for_pixel(c, 100, 50);

	return (0);
}
