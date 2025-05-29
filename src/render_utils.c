
#include "minirt.h"

int	set_viewport_upper_left(t_minirt *minirt)
{
	t_vec3	focal_length_v;
	t_vec3	viewport_center;

	focal_length_v = vec3_double_multiplication(minirt->render->camera_dir, minirt->render->focal_length);
	viewport_center = vec3_vec_addition(minirt->render->camera_center, focal_length_v);
	minirt->render->viewport_upper_left = vec3_vec_addition(
			viewport_center,
			vec3_vec_substraction(
				vec3_reverse(vec3_int_division(minirt->render->viewport_u, 2)),
				vec3_int_division(minirt->render->viewport_v, 2)));

	return (0);
}
// pixel00 = (viewport_upper_left + (0.5 * (pixel_delta_u + pixel_delta_v)))
int	set_pixel00_loc(t_minirt *minirt)
{
	minirt->render->pixel00_loc = vec3_vec_addition(
			minirt->render->viewport_upper_left,
			vec3_double_multiplication(
				vec3_vec_addition(
					minirt->render->pixel_delta_u,
					minirt->render->pixel_delta_v
					),
				0.5
				)
			);

	return (0);
}

t_vec3	get_pixel_center(int i, int j, t_render	*render)
{
	return (vec3_vec_addition(
			vec3_vec_addition(
				vec3_int_multiplication(render->pixel_delta_u, i),
				vec3_int_multiplication(render->pixel_delta_v, j)),
			render->pixel00_loc));
}

int	set_ray_direction(t_vec3 *ray_direction,
	t_render *render, t_vec3 *pixel_center)
{
	copy_vec3(ray_direction, pixel_center);
	vec3_substract_inplace(ray_direction, &render->camera_center);
	return (0);
}

int	is_debug_pixel(int i, int j)
{
	if (i == DEBUG_PIXEL_I && j == DEBUG_PIXEL_J)
		return (1);
	return (0);
}
