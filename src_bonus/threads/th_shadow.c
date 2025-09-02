/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:54:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:54:46 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*th_get_shadow_hit(t_inter_list *lst, t_object *object)
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

static void	th_check_each_object(t_inter_list *shadow_list, t_scene *scene,
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
		get_intersection(&scene->objects[i], &new_r, shadow_list);
		i++;
	}
}

int	th_is_shadowed(t_scene *scene, t_comp *comp, t_inter_list *shadow_list)
{
	t_vec3			v;
	double			distance;
	t_inter			*hit;

	v = vec3_vec_substraction(comp->light.pos, comp->over_point);
	distance = vec3_exact_length(v);
	th_check_each_object(shadow_list, scene, comp, vec3_normalise(v));
	sort_inter(shadow_list);
	hit = get_hit(shadow_list);
	shadow_list->count = 0;
	if (hit && hit->t < distance)
		return (true);
	return (false);
}
