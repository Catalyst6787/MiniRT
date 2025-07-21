#include "minirt.h"

void	th_fill_intersection_table(t_minirt *minirt, t_inter_list *inter_list, t_inter_list *shadow_list)
{
	int	inter_count;

	inter_count = count_intersections(minirt->scene);
	inter_list->inters
		= malloc(sizeof(t_inter) * inter_count + 1);
	if (!inter_list->inters)
		quit(minirt, MALLOC_ERR);
	shadow_list->inters
		= malloc(sizeof(t_inter) * inter_count + 1);
	if (!shadow_list->inters)
		quit(minirt, MALLOC_ERR);
	ft_memset(inter_list->inters, 0, sizeof(t_inter) * inter_count);
	ft_memset(shadow_list->inters, 0, sizeof(t_inter) * inter_count);
	inter_list->capacity = inter_count;
	shadow_list->capacity = inter_count;
}

t_vec3	th_intersect_objects(t_minirt *minirt, t_ray *unique_ray, t_thread_data *th, t_inter_list *inter_list, t_inter_list *shadow_list)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;
	t_vec3			color;
	(void)th;

	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		r = ray_transform(*unique_ray, minirt->scene->objects[i].inv);
		get_intersection(&minirt->scene->objects[i],
			&r, inter_list);
		i++;
	}
	sort_inter(inter_list);
	hit = get_hit(inter_list);
	if (!hit)
		return (inter_list->count = 0, get_color(0, 0, 0));
	i = 0;
	color = get_vec3(0, 0, 0);
	set_computations(&comp, minirt->scene->lights[i], hit, unique_ray);
	while (i < minirt->scene->nb_light)
	{
		comp.light = *minirt->scene->lights[i];
		color = vec3_vec_addition(color, th_shade_hit(minirt->scene, &comp, shadow_list));
		shadow_list->count = 0;
		i++;
	}
	inter_list->count = 0;
	return (color);
}

void	*th_render_scene(void *th_arg)
{
	int				y;
	int				x;
	t_ray			ray;
	t_thread_data	*th;
	t_inter_list	inter_list;
	t_inter_list	shadow_list;

	th = (t_thread_data *)th_arg;
	th_fill_intersection_table(th->minirt, &inter_list, &shadow_list);
	y = 0;
	while (y < th->minirt->scene->camera->vsize)
	{
		x = th->start;
		while (x <= th->end)
		{
			inter_list.count = 0;
			shadow_list.count = 0;
			ray = ray_for_pixel(*th->minirt->scene->camera, x, y);
			put_pixel(th->minirt,
				color_to_int(th_intersect_objects(th->minirt, &ray, th, &inter_list, &shadow_list)), x, y);
			x+= th->minirt->render->pixel_size;;
		}
		y+= th->minirt->render->pixel_size;
	}
	free(inter_list.inters);
	free(shadow_list.inters);
	return (NULL);
}
