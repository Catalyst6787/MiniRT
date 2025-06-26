#include "minirt.h"

t_inter	*get_shadow_hit(t_inter_list *lst)
{
	// int	i;

	// i = 0;
	if (lst->count > 2)
		return (&lst->inters[0]);
	return (NULL);
}

int	is_shadowed(t_render *render, t_scene *scene, t_vec3 point)
{
	t_vec3			v;
	double			distance;
	t_vec3			direction;
	t_ray			r;
	int				i;
	t_inter			*hit;

	render->shadow_list.count = 0;
	i = 0;
	v = vec3_vec_substraction(scene->light->pos, point);
	distance = vec3_exact_length(v);
	direction = vec3_normalise(v);
	r = get_ray(point, direction);
	debug_print_ray(&r);
	while (i < scene->nb_objects)
	{
		r = ray_transform(r, scene->objects[i].inv);
		get_intersection(&scene->objects[i], r, &render->shadow_list);
		i++;
	}
	sort_inter(&render->shadow_list);
	debug_print_inter_list(&render->shadow_list);
	i = 0;
	hit = get_hit(&render->shadow_list);
	// hit = get_shadow_hit(&render->shadow_list);
	// hit = &render->shadow_list.inters[0];
	if (hit && hit->t < distance)
		return (true);
	return (false);
}

t_vec3	shade_hit(t_render *render, t_scene *scene, t_comp *comp)
{
	bool	shadowed;

	shadowed = is_shadowed(render, scene, comp->over_point);
	return (get_lighting(comp, shadowed));
}
