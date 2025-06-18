
#include "minirt.h"
#include "ray.h"
#include "vec3.h"
#include <float.h>
#include <math.h>

//returns color at intersection
t_vec3	shade_intersection(t_inter *hit, t_ray r, t_minirt *minirt)
{
	t_lighting		l;
	const t_sphere	*intersected_sphere;

	ft_memset(&l, 0, sizeof(t_lighting));
	l.eyev = vec3_reverse(r.dir);
	l.light = *minirt->scene->light;
	intersected_sphere = hit->obj;
	// PRINT_DEBUG("%p\n", (void*)intersected_sphere);
	l.m = intersected_sphere->material;
	l.pos = ray_at(hit->t, r);
	l.normalv = get_normal_at(hit->obj, l.pos);
	return (get_lighting(l));
}


int	intersect_objects(t_minirt *minirt, t_ray unique_ray, int x, int y)
{
	int				i;
	t_ray			r;
	t_inter			*hit;

	i = 0;
	while (i < minirt->scene->nb_sphere)
	{
		r = ray_transform(unique_ray, minirt->scene->spheres[i]->inv);
		r.dir = vec3_normalise(r.dir);
		get_sphere_inter(minirt->scene->spheres[i],
			r, &minirt->render->inter_list);
		i++;
	}
	i = 0;
	// while (i < minirt->scene->nb_plane)
	// {
	// 	r = ray_transform(unique_ray, minirt->scene->planes[i]->inv);
	// 	r.dir = vec3_normalise(r.dir);
	// 	get_plane_inter(minirt->scene->planes[i], r, &minirt->render->inter_list);
	// 	i++;
	// }
	hit = get_hit(&minirt->render->inter_list);
	sort_inter(&minirt->render->inter_list);
	if (!hit)
		my_mlx_pixel_put(minirt, x, y, color_to_int(get_color(0, 0, 0)));
	else
		my_mlx_pixel_put(minirt, x, y, color_to_int(shade_intersection(hit, r, minirt)));
	minirt->render->inter_list.count = 0;
	return (0);
}

int	render_line(t_minirt *minirt, double world_y, int y)
{
	int		x;
	double	world_x;
	t_ray	unique_ray;

	x = 0;
	while (x < minirt->render->canva_width)
	{
		world_x = minirt->render->pixel_size * x - minirt->render->half;
		minirt->render->wall_point = get_point3(world_x, world_y,
				minirt->render->wall_distance);
		unique_ray = get_ray(
				minirt->render->original_ray.origin,
				vec3_normalise(
					vec3_vec_substraction(
						minirt->render->wall_point,
						minirt->render->original_ray.origin)));
		intersect_objects(minirt, unique_ray, x, y);
		x++;
	}
	return (0);
}

int	render_scene(t_minirt *minirt)
{
	int		y;
	double	world_y;

	if (!minirt)
		quit(minirt, "render_scene: NULL prt!");
	minirt->render->wall_distance = 10;
	minirt->render->wall_size = 7;
	minirt->render->canva_width = WIN_W;
	minirt->render->canva_height = WIN_H;
	minirt->render->pixel_size = minirt->render->wall_size
		/ minirt->render->canva_height;
	minirt->render->half = minirt->render->wall_size / 2;
	y = 0;
	minirt->render->original_ray = get_ray(
			get_point3(0, 0, -5),
			get_vec3(0, 0, 1));
	while (y < minirt->render->canva_height)
	{
		world_y = minirt->render->half - minirt->render->pixel_size * y;
		render_line(minirt, world_y, y);
		y++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	return (0);
}
