#include "minirt.h"
#include "ray.h"
#include "vec3.h"
#include <float.h>
#include <math.h>



int	intersect_objects(t_minirt *minirt, t_ray unique_ray, int x, int y)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;

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
	sort_inter(&minirt->render->inter_list);
	hit = get_hit(&minirt->render->inter_list);
	if (!hit)
		my_mlx_pixel_put(minirt, x, y, color_to_int(get_color(0, 0, 0)));
	else
	{
		comp = get_computations(minirt->scene, hit, unique_ray);
		my_mlx_pixel_put(minirt, x, y, color_to_int(get_lighting(comp)));
	}
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
			minirt->scene->camera->pos,
			minirt->scene->camera->dir);
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
