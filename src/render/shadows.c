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

static void	check_each_object(t_render *render, t_scene *scene,
	t_comp *comp, t_vec3 direction)
{
	int		i;
	t_ray	new_r;

	i = 0;
	while (i < scene->nb_objects)
	{
		new_r = ray_transform(
				get_ray(comp->over_point, direction),
				scene->objects[i].inv);
		get_intersection(&scene->objects[i], &new_r, &render->shadow_list);
		i++;
	}
}

int	is_shadowed(t_render *render, t_scene *scene, t_comp *comp)
{
	t_vec3			v;
	double			distance;
	t_inter			*hit;

	v = vec3_vec_substraction(scene->light->pos, comp->over_point);
	distance = vec3_exact_length(v);
	check_each_object(render, scene, comp, vec3_normalise(v));
	sort_inter(&render->shadow_list);
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
