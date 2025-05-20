/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   camera.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lfaure <lfaure@student.42lausanne.ch>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/07 16:33:19 by lfaure			#+#	#+#			 */
/*   Updated: 2025/05/09 17:59:07 by lfaure		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

int	init_render(t_render *render)
{
	render->focal_length = FOCAL_LEN;
	render->viewport_height = VIEWPORT_H;
	render->viewport_width = render->viewport_height
		* ((double)(WIN_W) / (double)WIN_H);
	render->camera_center = vec3_new_alloc(0, 0, 0);
	render->viewport_u = vec3_new_alloc(render->viewport_width, 0, 0);
	render->viewport_v = vec3_new_alloc(0, -render->viewport_height, 0);
	render->pixel_delta_u = vec3_dup_alloc(render->viewport_u);
	vec3_divide_by_inplace(render->pixel_delta_u, (double)WIN_W);
	render->pixel_delta_v = vec3_dup_alloc(render->viewport_v);
	vec3_divide_by_inplace(render->pixel_delta_v, (double)WIN_H);
	set_viewport_upper_left(render);
	set_pixel00_loc(render);
	return (0);
}

int	free_render(t_render *render)
{
	if (!render)
		return (ft_printf("Error. free_render: got passed null pointer"), 1);
	if (render->camera_center)
		free(render->camera_center);
	render->camera_center = NULL;
	if (render->viewport_u)
		free(render->viewport_u);
	render->viewport_u = NULL;
	if (render->viewport_v)
		free(render->viewport_v);
	render->viewport_v = NULL;
	if (render->pixel_delta_u)
		free(render->pixel_delta_u);
	render->pixel_delta_u = NULL;
	if (render->pixel_delta_v)
		free(render->pixel_delta_v);
	render->pixel_delta_v = NULL;
	if (render->viewport_upper_left)
		free(render->viewport_upper_left);
	render->viewport_upper_left = NULL;
	if (render->pixel00_loc)
		free(render->pixel00_loc);
	render->pixel00_loc = NULL;
	return (0);
}

int	ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere)
{
	t_vec3		unit_dir;
	double		a;
	t_vec3		blue;

	assert(r);
	assert(r->dir);
	assert(r->origin);
	assert(color);
	vec3_init(&blue, 0.5, 0.7, 1.0);
	vec3_copy(&unit_dir, r->dir);
	a = 0.5 * (unit_dir.y + 1.0);
	vec3_normalise_inplace(&unit_dir);
	if (DEBUG && is_debug_pixel)
		debug_pixel(r);
	vec3_multiply_by_inplace(color, 1.0 - a);
	vec3_multiply_by_inplace(&blue, a);
	vec3_add_inplace(color, &blue);
	if (hit_sphere(sphere, r))
		vec3_init(color, 1, 0, 0);
	return (0);
}

// STACK ALLOC to go faster, change to heap if overflow.
int	render_pixel(int i, int j, t_render	*render, t_minirt *minirt, t_sphere *sphere)
{
	t_vec3	pixel_center;
	t_vec3	ray_direction;
	t_ray	ray;
	t_vec3	ray_or;
	t_vec3	ray_dir;
	t_vec3	color;

	vec3_init(&ray_or, 0, 0, 0);
	vec3_init(&ray_dir, 0, 0, 0);
	ray.origin = &ray_or;
	ray.dir = &ray_dir;
	vec3_init(&color, 1, 1, 1);
	vec3_init(&pixel_center, 0, 0, 0);
	vec3_init(&ray_direction, 0, 0, 0);
	set_pixel_center(&pixel_center, i, j, render);
	set_ray_direction(&ray_direction, render, &pixel_center);
	ray_init(&ray, render->camera_center, &ray_direction);
	ray_color(&ray, &color, is_debug_pixel(i, j), sphere);
	my_mlx_pixel_put(minirt, i, j, get_color_as_int(&color));
	return (0);
}

int	render_scene(t_minirt *minirt, t_mlx_data *mlx, t_scene *scene)
{
	int			j;
	int			i;
	t_render	*render;
	t_sphere	*sphere;

	sphere = sphere_new_alloc(vec3_new_alloc(0, 0, -1),
			0.5, vec3_new_alloc(1, 0, 0));
	j = 0;
	i = 0;
	(void)scene;
	render = ft_calloc(1, sizeof(t_render));
	if (!render)
		return (perror("Malloc error in render_scene"), 1);
	init_render(render);
	while (j < WIN_H)
	{
		if (DEBUG)
			ft_printf("Scanlines remaining: %d\n", WIN_H - j);
		while (i < WIN_W)
			render_pixel(i++, j, render, minirt, sphere);
		i = 0;
		j++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
	free_render(render);
	free_and_null((void **)&render);
	free(sphere->pos);
	free(sphere->color);
	free(sphere);
	return (0);
}
