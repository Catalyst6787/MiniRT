#include "matrice.h"
#include "minirt.h"
#include "ray.h"
#include "render.h"
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
	assert(vec3_isequal(r.origin, get_point3(0, 0, 0)));
	assert(vec3_isequal(r.dir, get_vec3(0, 0, -1)));

	// Constructing a ray through a corner of the canvas
	c = get_camera(201, 101, M_PI / 2);
	r = ray_for_pixel(c, 0, 0);
	assert(vec3_isequal(r.origin, get_point3(0, 0, 0)));
	assert(vec3_isequal(r.dir, get_vec3(0.66519, 0.33259, -0.66851)));

	// Constructig a ray when the camera is transformed
	c = get_camera(201, 101, M_PI / 2);
	c.transform = multiply_matrix(get_rotation_matrix_y(M_PI / 4), get_translation_matrix(get_vec3(0, -2, 5)));
	c.inv = get_inversed_matrix(c.transform);
	r = ray_for_pixel(c, 100, 50);
	assert(vec3_isequal(r.origin, get_point3(0, 2, -5)));
	assert(vec3_isequal(r.dir, get_vec3(sqrt(2) / 2, 0, -sqrt(2) / 2)));

	return (0);
}
