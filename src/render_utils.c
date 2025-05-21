
#include "minirt.h"

int	set_viewport_upper_left(t_render *render)
{
	t_vec3	focal_length_v;
	t_vec3	viewport_u_div2;
	t_vec3	viewport_v_div2;
	t_vec3	upper_left;

	
	upper_left = get_vec3(0, 0, 0);
	focal_length_v = get_vec3(0, 0, render->focal_length);
	upper_left = vec3_vec_substraction(upper_left, focal_length_v);
	viewport_u_div2 = get_vec3(render->viewport_u->x, render->viewport_u->y, render->viewport_u->z);
	viewport_u_div2 = vec3_int_division(viewport_u_div2, 2);
	upper_left = vec3_vec_substraction(upper_left, viewport_u_div2);
	viewport_v_div2 = get_vec3(render->viewport_v->x, render->viewport_v->y, render->viewport_v->z);
	viewport_v_div2 = vec3_int_division(viewport_v_div2, 2);
	upper_left = vec3_vec_substraction(upper_left, viewport_v_div2);
	render->viewport_upper_left = vec3_dup_alloc(&upper_left);

	return (0);
}

int	set_pixel00_loc(t_render *render)
{
	t_vec3	*pixel_delt_uv;

	render->pixel00_loc = vec3_dup_alloc(render->viewport_upper_left);
	pixel_delt_uv = vec3_dup_alloc(render->pixel_delta_u);
	vec3_add_inplace(pixel_delt_uv, render->pixel_delta_v);
	vec3_multiply_by_inplace(pixel_delt_uv, 0.5);
	vec3_add_inplace(render->pixel00_loc, pixel_delt_uv);
	free(pixel_delt_uv);
	pixel_delt_uv = NULL;
	return (0);
}

int	set_pixel_center(t_vec3	*pixel_center, int i, int j, t_render	*render)
{
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;

	copy_vec3(&pixel_delta_u, render->pixel_delta_u);
	copy_vec3(&pixel_delta_v, render->pixel_delta_v);
	vec3_multiply_by_inplace(&pixel_delta_u, i);
	vec3_multiply_by_inplace(&pixel_delta_v, j);
	vec3_add_inplace(&pixel_delta_u, &pixel_delta_v);

	copy_vec3(pixel_center, render->pixel00_loc);
	vec3_add_inplace(pixel_center, &pixel_delta_u);
	return (0);
}

int	set_ray_direction(t_vec3 *ray_direction,
	t_render *render, t_vec3 *pixel_center)
{
	copy_vec3(ray_direction, pixel_center);
	vec3_substract_inplace(ray_direction, render->camera_center);
	return (0);
}

int	is_debug_pixel(int i, int j)
{
	if (i == DEBUG_PIXEL_I && j == DEBUG_PIXEL_J)
		return (1);
	return (0);
}
