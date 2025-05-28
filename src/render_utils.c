
#include "minirt.h"

int	set_viewport_upper_left(t_minirt *minirt)
{
	t_vec3	focal_length_v;

	focal_length_v = vec3_double_multiplication(minirt->render->camera_dir, minirt->render->focal_length);
	minirt->render->viewport_upper_left = vec3_vec_addition(
			focal_length_v,
			vec3_vec_substraction(
				vec3_reverse(vec3_int_division(minirt->render->viewport_u, 2)),
				vec3_int_division(minirt->render->viewport_v, 2)));

	return (0);
}

int	set_pixel00_loc(t_minirt *minirt)
{
	t_vec3	pixel_delt_uv;

	copy_vec3(&minirt->render->pixel00_loc, &minirt->render->viewport_upper_left);
	copy_vec3(&pixel_delt_uv, &minirt->render->pixel_delta_u);
	vec3_add_inplace(&pixel_delt_uv, &minirt->render->pixel_delta_v);
	vec3_multiply_by_inplace(&pixel_delt_uv, 0.5);
	vec3_add_inplace(&minirt->render->pixel00_loc, &pixel_delt_uv);
	return (0);
}

int	set_pixel_center(t_vec3	*pixel_center, int i, int j, t_render	*render)
{
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;

	copy_vec3(&pixel_delta_u, &render->pixel_delta_u);
	copy_vec3(&pixel_delta_v, &render->pixel_delta_v);
	vec3_multiply_by_inplace(&pixel_delta_u, i);
	vec3_multiply_by_inplace(&pixel_delta_v, j);
	vec3_add_inplace(&pixel_delta_u, &pixel_delta_v);
	copy_vec3(pixel_center, &render->pixel00_loc);
	vec3_add_inplace(pixel_center, &pixel_delta_u);
	return (0);
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
