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

int	set_ray_direction(t_vec3 *ray_direction, t_render *render, t_vec3 *pixel_center)
{
	vec3_copy(ray_direction, pixel_center);
	vec3_substract_inplace(ray_direction, render->camera_center);
	return (0);
}

int	ray_color(const t_ray *r, t_vec3 *color)
{
	(void)r;
	color->x = 1;
	color->y = 1;
	color->z = 1;
	return (0);
}

int	get_color_as_int(t_vec3 *color)
{
	int red   = (int)(color->x * 255.0);
	int green = (int)(color->y * 255.0);
	int blue  = (int)(color->z * 255.0);

	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	return (red << 16) | (green << 8) | blue;
}

// STACK ALLOC to go faster, change to heap if overflow.
int	render_pixel(int i, int j, t_render	*render, t_mlx_data *mlx)
{
	t_vec3	pixel_center;
	t_vec3	ray_direction;
	t_ray	*ray;
	t_vec3	color;

	ray = ray_default_alloc();
	vec3_init(&pixel_center, 0, 0, 0);
	vec3_init(&ray_direction, 0, 0, 0);
	set_pixel_center(&pixel_center, i, j, render);
	set_ray_direction(&ray_direction, render, &pixel_center);
	ray_init(ray, render->camera_center, &ray_direction);

	ray_color(ray, &color);
	my_mlx_pixel_put(mlx, i, j, get_color_as_int(&color));
	free(ray->dir);
	free(ray->origin);
	free(ray);
	return (0);
}

int	render_scene(t_mlx_data *mlx, t_scene *scene)
{
	(void)scene;
	int			j = 0;
	int			i = 0;
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (perror("Malloc error in render_scene"), 1);
	// ft_memset(render, '\0', sizeof(t_render));
	init_render(render);
	while (j < WIN_H)
	{
		ft_printf("Scanlines remaining: %d\n", WIN_H - j);
		while (i < WIN_W)
		{
			render_pixel(i, j, render, mlx);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
	return (0);
}
