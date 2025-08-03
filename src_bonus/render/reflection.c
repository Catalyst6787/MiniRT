#include "minirt.h"

t_vec3	reflected_color(t_comp *comp, t_minirt *minirt, unsigned int depth)
{
	t_ray	reflect_ray;
	t_vec3	color;

	if (depth == REFLECTION_MAX_DEPTH || !minirt)
		return(get_color(0, 0, 0));
	minirt->render->inter_list.count = 0;
	minirt->render->shadow_list.count = 0;
	if (double_isequal(comp->object->material.reflective, 0.0))
		return(get_vec3(0, 0, 0));
	reflect_ray = get_ray(comp->over_point, comp->reflectv);
	color = intersect_objects(minirt, &reflect_ray, depth + 1);
	return (vec3_double_multiplication(color, comp->object->material.reflective));
}
