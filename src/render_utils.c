/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:48:06 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 11:58:19 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_viewport_upper_left(t_render *render)
{
	t_vec3	*focal_length_v;
	t_vec3	*viewport_u_div2;
	t_vec3	*viewport_v_div2;

	render->viewport_upper_left = vec3_dup_alloc(render->camera_center);
	focal_length_v = vec3_new_alloc(0, 0, render->focal_length);
	vec3_substract_inplace(render->viewport_upper_left, focal_length_v);
	viewport_u_div2 = vec3_dup_alloc(render->viewport_u);
	vec3_divide_by_inplace(viewport_u_div2, 2);
	vec3_substract_inplace(render->viewport_upper_left, viewport_u_div2);
	viewport_v_div2 = vec3_dup_alloc(render->viewport_v);
	vec3_divide_by_inplace(viewport_v_div2, 2);
	vec3_substract_inplace(render->viewport_upper_left, viewport_v_div2);
	free(focal_length_v);
	focal_length_v = NULL;
	free(viewport_u_div2);
	viewport_u_div2 = NULL;
	free(viewport_v_div2);
	viewport_v_div2 = NULL;
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

	vec3_copy(&pixel_delta_u, render->pixel_delta_u);
	vec3_copy(&pixel_delta_v, render->pixel_delta_v);
	vec3_multiply_by_inplace(&pixel_delta_u, i);
	vec3_multiply_by_inplace(&pixel_delta_v, j);
	vec3_add_inplace(&pixel_delta_u, &pixel_delta_v);

	vec3_copy(pixel_center, render->pixel00_loc);
	vec3_add_inplace(pixel_center, &pixel_delta_u);
	return (0);
}

int	set_ray_direction(t_vec3 *ray_direction,
	t_render *render, t_vec3 *pixel_center)
{
	vec3_copy(ray_direction, pixel_center);
	vec3_substract_inplace(ray_direction, render->camera_center);
	return (0);
}
