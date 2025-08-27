#include "minirt.h"

t_vec3	reflected_color(t_comp *comp, t_minirt *minirt, unsigned int depth)
{
	t_ray	reflect_ray;
	t_vec3	color;

	if (depth == minirt->render->max_depth || !minirt)
		return(get_color(0, 0, 0));
	minirt->render->inter_list.count = 0;
	minirt->render->shadow_list.count = 0;
	if (double_isequal(comp->object->material.reflective, 0.0))
		return(get_vec3(0, 0, 0));
	reflect_ray = get_ray(comp->over_point, comp->reflectv);
	color = intersect_objects(minirt, &reflect_ray, depth + 1);
	return (vec3_double_multiplication(color, comp->object->material.reflective));
}

t_vec3	th_reflected_color(t_comp *comp, t_minirt *minirt, t_thread_data *th, unsigned int depth)
{
	t_ray	reflect_ray;
	t_vec3	color;

	th->inter_list.count = 0;
	th->shadow_list.count = 0;
	if (depth == minirt->render->max_depth || !minirt)
		return(get_color(0, 0, 0));
	if (double_isequal(comp->object->material.reflective, 0.0))
		return(get_vec3(0, 0, 0));
	reflect_ray = get_ray(comp->over_point, comp->reflectv);
	color = th_intersect_objects(minirt, &reflect_ray, th, depth + 1);
	return (vec3_double_multiplication(color, comp->object->material.reflective));
}
