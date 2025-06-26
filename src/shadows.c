#include "minirt.h"

t_inter	*get_shadow_hit(t_inter_list *lst, t_object *object)
{
	int	i;

	i = 0;
	while (i < lst->count)
	{
		if (lst->inters[i].obj != (t_object *)object)
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
	t_ray			r;
	int				i;
	t_inter			*hit;
	(void)			direction;
	(void) hit;

	i = 0;
	v = vec3_vec_substraction(scene->light->pos, comp->over_point);
	distance = vec3_exact_length(v);
	direction = vec3_normalise(v);
	PRINT_DEBUG("dist : %.2f\n", distance);
	r = get_ray(comp->over_point, direction);
	debug_print_ray(&r);
	while (i < scene->nb_objects)
	{
		r = ray_transform(r, scene->objects[i].inv);
		get_intersection(&scene->objects[i], r, &render->shadow_list);
		i++;
	}
	sort_inter(&render->shadow_list);
	debug_print_inter_list(&render->shadow_list);
	hit = get_hit(&render->shadow_list);
	render->shadow_list.count = 0;
	if (hit && hit->t < distance)
		return (PRINT_DEBUG("TRUE\n\n"), true);
	return (PRINT_DEBUG("FALSE\n\n"), false);
}

t_vec3	shade_hit(t_render *render, t_scene *scene, t_comp *comp)
{
	bool	shadowed;

	shadowed = is_shadowed(render, scene, comp);
	return (get_lighting(comp, shadowed));
}
