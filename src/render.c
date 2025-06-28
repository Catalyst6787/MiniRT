#include "minirt.h"
#include <float.h>
#include <math.h>

void	set_computations(t_comp *comp_out, t_scene *scene, t_inter *hit, t_ray r)
{
	ft_memset(comp_out, 0, sizeof(t_comp));
	comp_out->eyev =  vec3_reverse(r.dir);
	comp_out->light = *scene->light;
	comp_out->m = hit->obj->material;
	comp_out->point = ray_at(hit->t, r);
	comp_out->normalv = get_sphere_normal_at(hit->obj, comp_out->point);
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


int	get_intersection(t_object *object, t_ray ray, t_inter_list *list)
{
	if (object->type == SPHERE)
		get_sphere_inter(object, ray, list);


	/*       ADD NEXT :       */

	// else if (object->type == PLANE)
	// 	get_plane_inter(object, ray, list);
	// else if (object->type == CYLINDER)
	// 	get_cylinder_inter(object, ray, list);
	return (0);
}


t_vec3	intersect_objects(t_minirt *minirt, t_ray unique_ray)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;

	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		r = ray_transform(unique_ray, minirt->scene->objects[i].inv);
		get_intersection(&minirt->scene->objects[i], r, &minirt->render->inter_list);
		i++;
	}
	sort_inter(&minirt->render->inter_list);
	hit = get_hit(&minirt->render->inter_list);
	if (!hit)
		return (minirt->render->inter_list.count = 0, get_color(0, 0, 0));
	else
	{
		set_computations(&comp, minirt->scene, hit, unique_ray);
		return (minirt->render->inter_list.count = 0, shade_hit(minirt->render, minirt->scene, &comp));
	}
	minirt->render->inter_list.count = 0;
}

void	print_pixel(t_minirt *minirt, int color, int x, int y)
{
	int	x_off;
	int	y_off;

	y_off = y;
	while (y_off < y + PIXEL_SIZE_MULT && y_off < minirt->scene->camera->vsize)
	{
		x_off = x;
		while (x_off < x + PIXEL_SIZE_MULT  && x_off < minirt->scene->camera->hsize)
		{
			my_mlx_pixel_put(minirt, x_off, y_off, color);
			x_off++;
		}
		y_off++;
	}
}

int	render_scene(t_minirt *minirt)
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	debug_print_objects_pointers(minirt->scene);
	minirt->render->debug_y = 0;
	if (!minirt)
		quit(minirt, "render_scene: NULL prt!");
	// print_camera_data(minirt);
	while (y < minirt->scene->camera->vsize)
	{
		x = 0;
		while(x < minirt->scene->camera->hsize)
		{
			ray = ray_for_pixel(*minirt->scene->camera, x, y);
			print_pixel(minirt, color_to_int(intersect_objects(minirt, ray)), x, y);
			x += PIXEL_SIZE_MULT;
		}
		y += PIXEL_SIZE_MULT;
		minirt->render->debug_y++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	return (0);
}

t_vec3	render_one_pixel_test(t_minirt *minirt, int x, int y)
{
	t_ray	ray;

	ray = ray_for_pixel(*minirt->scene->camera, x, y);
	return (intersect_objects(minirt, ray));
}
