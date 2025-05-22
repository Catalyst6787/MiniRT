
#include "minirt.h"

int	init_render(t_render *render)
{
	render->focal_length = FOCAL_LEN;
	render->viewport_height = VIEWPORT_H;
	render->viewport_width = render->viewport_height
		* ((double)(WIN_W) / (double)WIN_H);
	render->camera_center = get_vec3(0, 0, 0);
	render->viewport_u = get_vec3(render->viewport_width, 0, 0);
	render->viewport_v = get_vec3(0, -render->viewport_height, 0);
	render->pixel_delta_u = vec3_double_division(render->viewport_u, (double)(WIN_W));
	render->pixel_delta_v = vec3_double_division(render->viewport_v, (double)(WIN_H));
	set_viewport_upper_left(render);
	set_pixel00_loc(render);
	return (0);
}

int	ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere)
{
	t_vec3		unit_dir;
	double		a;
	t_vec3		blue;

	blue = get_vec3(0.5, 0.7, 1.0);
	unit_dir = vec3_dup(*r->dir);
	a = 0.5 * (unit_dir.y + 1.0);
	unit_dir = vec3_normalise(unit_dir);
	if (DEBUG && is_debug_pixel)
		debug_pixel(r);
	vec3_multiply_by_inplace(color, 1.0 - a);
	vec3_multiply_by_inplace(&blue, a);
	vec3_add_inplace(color, &blue);
	if (hit_sphere(sphere, r))
		set_vec3(color, 1, 0, 0);
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

	set_vec3(&ray_or, 0, 0, 0);
	set_vec3(&ray_dir, 0, 0, 0);
	ray.origin = &ray_or;
	ray.dir = &ray_dir;
	set_color(&color, 1, 1, 1);
	set_vec3(&pixel_center, 0, 0, 0);
	set_vec3(&ray_direction, 0, 0, 0);
	set_pixel_center(&pixel_center, i, j, render);
	set_ray_direction(&ray_direction, render, &pixel_center);
	ray_init(&ray, &render->camera_center, &ray_direction);
	ray_color(&ray, &color, is_debug_pixel(i, j), sphere);
	my_mlx_pixel_put(minirt, i, j, get_color_as_int(&color));
	return (0);
}


int	render_scene(t_minirt *minirt)
{
	int			j;
	int			i;
	t_render	*render;
	t_sphere	*sphere;

	sphere = minirt->scene->spheres[0];
	j = 0;
	i = 0;
	render = ft_calloc(1, sizeof(t_render));
	if (!render)
		return (perror("Malloc error in render_scene"), 1);
	init_render(render);
	while (j < WIN_H)
	{
		i = 0;
		if (DEBUG)
			ft_printf("Scanlines remaining: %d\n", WIN_H - j);
		while (i < WIN_W)
			render_pixel(i++, j, render, minirt, sphere);
		j++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	free_and_null((void **)&render);
	return (0);
}
