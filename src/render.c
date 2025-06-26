#include "minirt.h"
#include "ray.h"
#include "vec3.h"
#include <float.h>
#include <math.h>

static void	init_render(t_render *render, t_scene *scene)
{
	render->wall_distance = 10;
	render->wall_size = 7;
	render->canva_width = WIN_W;
	render->canva_height = WIN_H;
	render->pixel_size = render->wall_size
		/ render->canva_height;
	render->half = render->wall_size / 2;
	render->original_ray = get_ray(scene->camera->pos,
									scene->camera->dir);
}

void	set_computations(t_comp *comp_out, t_scene *scene, t_inter *hit, t_ray r)
{
	ft_memset(comp_out, 0, sizeof(t_comp));
	comp_out->eyev =  vec3_reverse(r.dir);
	comp_out->light = *scene->light;
	comp_out->m = hit->obj->material;
	comp_out->point = ray_at(hit->t, r);
	comp_out->normalv = get_sphere_normal_at(hit->obj, comp_out->point);
	comp_out->t = hit->t;
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

int	intersect_objects(t_minirt *minirt, t_ray unique_ray, int x, int y)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;

	i = 0;
	PRINT_DEBUG("x = [%d] y = [%d]\n", x, y);
	while (i < minirt->scene->nb_objects)
	{
		r = ray_transform(unique_ray, minirt->scene->objects[i].inv);
		get_intersection(&minirt->scene->objects[i], r, &minirt->render->inter_list);
		i++;
	}
	// debug_print_inter_list(&minirt->render->inter_list);
	sort_inter(&minirt->render->inter_list);
	hit = get_hit(&minirt->render->inter_list);
	if (!hit)
		my_mlx_pixel_put(minirt, x, y, color_to_int(get_color(0, 0, 0)));
	else
	{
		set_computations(&comp, minirt->scene, hit, unique_ray);
		my_mlx_pixel_put(minirt, x, y, color_to_int(shade_hit(minirt->render,
														minirt->scene, &comp)));
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
	minirt->render->debug_x = 0;
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
		minirt->render->debug_x++;
	}
	return (0);
}

int	render_scene(t_minirt *minirt)
{
	int		y;
	double	world_y;

	y = 0;
	debug_print_objects_pointers(minirt->scene);
	minirt->render->debug_y = 0;
	if (!minirt)
		quit(minirt, "render_scene: NULL prt!");
	init_render(minirt->render, minirt->scene);
	while (y < minirt->render->canva_height)
	{
		world_y = minirt->render->half - minirt->render->pixel_size * y;
		render_line(minirt, world_y, y);
		y++;
		minirt->render->debug_y++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	return (0);
}
