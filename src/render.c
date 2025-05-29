
#include "minirt.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>

int	set_focal_length(t_minirt *minirt)
{
	double	fov_y_rad;

	fov_y_rad = minirt->scene->camera->fov * M_PI / 180;
	minirt->render->focal_length = VIEWPORT_H / (2.0 * tan(fov_y_rad / 2.0));
	return (0);
}

int	init_render(t_minirt *minirt)
{
	minirt->render->viewport_height = VIEWPORT_H;
	// minirt->render->focal_length = FOCAL_LEN;
	set_focal_length(minirt);
	minirt->render->viewport_width = minirt->render->viewport_height
		* ((double)(WIN_W) / (double)WIN_H);
	minirt->render->camera_center = vec3_dup(*minirt->scene->camera->pos);
	minirt->render->camera_dir = vec3_normalise(*minirt->scene->camera->dir);
	minirt->render->world_up = get_vec3(0, 1, 0);
	minirt->render->right = vec3_normalise(vec3_cross(minirt->render->camera_dir, minirt->render->world_up));
	minirt->render->up = vec3_cross(minirt->render->right, minirt->render->camera_dir);
	minirt->render->viewport_u = vec3_double_multiplication(minirt->render->right, minirt->render->viewport_width);
	minirt->render->viewport_v = vec3_double_multiplication(minirt->render->up, -minirt->render->viewport_height);
	minirt->render->pixel_delta_u = vec3_double_division(minirt->render->viewport_u, (double)(WIN_W));
	minirt->render->pixel_delta_v = vec3_double_division(minirt->render->viewport_v, (double)(WIN_H));
	// printf("up : %.4f %.4f %.4f\n", minirt->render->.x, minirt->render->.y , minirt->render->.z);

	set_viewport_upper_left(minirt);
	set_pixel00_loc(minirt);

	return (0);
}

int	ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere)
{
	(void)is_debug_pixel;
	double	t;
	double	a;
	t_vec3	normal;
	t_vec3	blue;
	t_vec3	unit_direction;

	blue = get_vec3(0.5, 0.7, 1.0);
	t = hit_sphere(sphere, r);
	if (t > 0.0)
	{
		normal = vec3_normalise(vec3_vec_substraction(ray_at(t, r), *sphere->pos));
		*color = vec3_double_multiplication(get_vec3(normal.x + 1, normal.y + 1, normal.z + 1), 0.5);
		return (0);
	}
	unit_direction = vec3_normalise(*r->dir);
	a = 0.5 * (unit_direction.y + 1.0);
	*color = vec3_vec_addition(vec3_double_multiplication(get_vec3(1, 1, 1), (1.0 - a)), vec3_double_multiplication(blue, a));
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

	ray_or = vec3_dup(minirt->render->camera_center);
	ray_dir = vec3_dup(minirt->render->camera_dir);
	ray.origin = &ray_or;
	ray.dir = &ray_dir;
	pixel_center = get_pixel_center(i, j, render);
	// vec3_vec_substraction(pixel_center, render->camera_center);
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

	if (init_render(minirt))
		quit(minirt, RENDER_INIT_ERR);
	render = minirt->render;
	sphere = minirt->scene->spheres[0];
	j = 0;
	i = 0;
	while (j < WIN_H)
	{
		i = 0;
		if (DEBUG)
			ft_printf("Scanlines remaining: %d\normal", WIN_H - j);
		while (i < WIN_W)
			render_pixel(i++, j, render, minirt, sphere);
		j++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	return (0);
}
