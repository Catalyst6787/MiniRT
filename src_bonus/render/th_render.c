#include "minirt.h"

t_vec3	th_shade_hit(t_render *render, t_scene *scene, t_comp comp)
{
	bool	shadowed;

	shadowed = is_shadowed(render, scene, &comp);
	return (get_lighting(&comp, shadowed));
}

t_vec3	th_intersect_objects(t_minirt *minirt, t_ray *unique_ray, t_thread_data *th)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;
	t_vec3			color;
	(void)th;

	i = 0;
	minirt->render->inter_list.count = 0;
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
	i = 0;
	color = get_vec3(0, 0, 0);
	set_computations(&comp, minirt->scene->lights[i], hit, unique_ray);
	while (i < minirt->scene->nb_light)
	{
		comp.light = *minirt->scene->lights[i];
		color = vec3_vec_addition(color, th_shade_hit(minirt->render, minirt->scene, comp));
		minirt->render->shadow_list.count = 0;
		i++;
	}
	// minirt->render->inter_list.count = 0;
	return (color);
}

void	*th_render_scene(void *th_arg)
{
	int				y;
	int				x;
	t_ray			ray;
	t_thread_data	*th;
	(void) ray;

	th = (t_thread_data *)th_arg;
	y = 0;
	if (!th->minirt)
		quit(th->minirt, "render_scene: NULL prt!");
	while (y < th->minirt->scene->camera->vsize)
	{
		x = th->start;
		while (x <= th->end)
		{
			ray = ray_for_pixel(*th->minirt->scene->camera, x, y);
			pthread_mutex_lock(&th->minirt->render->putpixel_mtx);
			put_pixel(th->minirt,
				color_to_int(th_intersect_objects(th->minirt, &ray, th)), x, y);
			pthread_mutex_unlock(&th->minirt->render->putpixel_mtx);
			x += th->minirt->render->pixel_size;
		}
		y += th->minirt->render->pixel_size;
	}
	return (NULL);
}
