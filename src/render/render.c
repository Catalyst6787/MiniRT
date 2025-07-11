#include "minirt.h"
#include <float.h>
#include <math.h>

void	set_computations(t_comp *comp_out,
		t_scene *scene, t_inter *hit, t_ray *r)
{
	ft_memset(comp_out, 0, sizeof(t_comp));
	comp_out->eyev = vec3_reverse(r->dir);
	comp_out->light = *scene->light;
	comp_out->m = hit->obj->material;
	comp_out->point = ray_at(hit->t, r);
	comp_out->normalv = get_object_normal_at(hit->obj, comp_out->point);
	comp_out->t = hit->t;
	comp_out->object = (t_object *)hit->obj;
	if (vec3_dot(comp_out->normalv, comp_out->eyev) < 0)
	{
		comp_out->inside = true;
		comp_out->normalv = vec3_reverse(comp_out->normalv);
	}
	else
	{
		comp_out->inside = false;
	}
	comp_out->over_point = vec3_vec_addition(comp_out->point,
			vec3_double_multiplication(comp_out->normalv, EPSILON));
}

t_vec3	intersect_objects(t_minirt *minirt, t_ray *unique_ray)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;

	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		r = ray_transform(*unique_ray, minirt->scene->objects[i].inv);
		get_intersection(&minirt->scene->objects[i],
			&r, &minirt->render->inter_list);
		i++;
	}
	sort_inter(&minirt->render->inter_list);
	hit = get_hit(&minirt->render->inter_list);
	if (!hit)
		return (minirt->render->inter_list.count = 0, get_color(0, 0, 0));
	else
	{
		set_computations(&comp, minirt->scene, hit, unique_ray);
		return (minirt->render->inter_list.count = 0,
			shade_hit(minirt->render, minirt->scene, &comp));
	}
	minirt->render->inter_list.count = 0;
	minirt->render->shadow_list.count = 0;
}

t_ray	ray_for_pixel(t_camera camera, double px, double py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	t_vec3	pixel;

	xoffset = (px + 0.5) * camera.pixel_size;
	yoffset = (py + 0.5) * camera.pixel_size;
	world_x = camera.half_width - xoffset;
	world_y = camera.half_height - yoffset;
	pixel = vec3_matrix_multiply(camera.inv, get_point3(world_x, world_y, -1));
	return (get_origin_direction(camera, pixel));
}

int	render_scene(t_minirt *minirt)
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	minirt->render->debug_y = 0;
	if (!minirt)
		quit(minirt, "render_scene: NULL prt!");
	while (y < minirt->scene->camera->vsize)
	{
		x = 0;
		minirt->render->debug_x = 0;
		while (x < minirt->scene->camera->hsize)
		{
			ray = ray_for_pixel(*minirt->scene->camera, x, y);
			put_pixel(minirt,
				color_to_int(intersect_objects(minirt, &ray)), x, y);
			x += minirt->render->pixel_size;
			minirt->render->debug_x = x;
		}
		y += minirt->render->pixel_size;
		minirt->render->debug_y = y;
	}
	display_image(minirt);
	return (0);
}
