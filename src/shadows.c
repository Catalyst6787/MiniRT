#include "minirt.h"

t_inter	*get_shadow_hit(t_inter_list *lst, t_object *object)
{
	int	i;

	i = 0;
	while (i < lst->count)
	{
		if (lst->inters[i].obj != object)
			return (&lst->inters[i]);
		i++;
	}
	return (NULL);
}

int	is_shadowed(t_render *render, t_scene *scene, t_comp *comp)
{
	t_vec3			v;
	double			distance;
	t_vec3			direction;
	t_ray			og_r;
	t_ray			new_r;
	int				i;
	t_inter			*hit;

	i = 0;
	v = vec3_vec_substraction(scene->light->pos, comp->over_point);
	distance = vec3_exact_length(v);
	direction = vec3_normalise(v);
	// PRINT_DEBUG("dist : %.2f\n", distance);
	og_r = get_ray(comp->over_point, direction);
	// debug_print_ray(&og_r);
	// PRINT_DEBUG("Point : %.2f %.2f %.2f\n", comp->over_point.x, comp->over_point.y, comp->over_point.z);
	while (i < scene->nb_objects)
	{
		new_r = ray_transform(og_r, scene->objects[i].inv);
		get_intersection(&scene->objects[i], &new_r, &render->shadow_list);
		i++;
	}
	sort_inter(&render->shadow_list);
	// debug_print_inter_list(&render->shadow_list);
	hit = get_hit(&render->shadow_list);
	render->shadow_list.count = 0;
	if (hit && hit->t < distance)
		return (true);
	return (false);
}

t_vec3	shade_hit(t_render *render, t_scene *scene, t_comp *comp)
{
	bool	shadowed;

	shadowed = is_shadowed(render, scene, comp);
	return (get_lighting(comp, shadowed));
}
