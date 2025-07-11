#include "minirt.h"

t_light	get_light(t_vec3 pos, double brightness, t_vec3 color)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	light.color = color;
	return (light);
}

static t_vec3	get_specular(double reflect_dot_eye, t_comp *comp)
{
	double	factor;

	factor = pow(reflect_dot_eye, comp->m.shininess);
	return (vec3_double_multiplication(
			vec3_double_multiplication(
				comp->light.color,
				comp->m.specular),
			factor));
}

static t_vec3	get_lighting_extra(t_comp *comp,
					t_vec3 light_vector, t_vec3 effective_color, t_vec3 ambient)
{
	double	light_dot_normal;
	double	reflect_dot_eye;
	t_vec3	diffuse;
	t_vec3	specular;

	light_dot_normal = vec3_dot(light_vector, comp->normalv);
	if (light_dot_normal < 0)
	{
		diffuse = get_color(0, 0, 0);
		specular = get_color(0, 0, 0);
	}
	else
	{
		diffuse = vec3_double_multiplication(effective_color,
				(comp->m.diffuse * light_dot_normal));
		reflect_dot_eye = vec3_dot(get_reflection(vec3_reverse(light_vector),
					comp->normalv), comp->eyev);
		if (reflect_dot_eye <= 0)
			specular = get_color(0, 0, 0);
		else
			specular = get_specular(reflect_dot_eye, comp);
	}
	return (vec3_vec_addition(ambient, vec3_vec_addition(diffuse, specular)));
}

t_vec3	get_lighting(t_comp	*comp, bool in_shadow)
{
	t_vec3	effective_color;
	t_vec3	light_vector;
	t_vec3	ambient;

	effective_color = vec3_vec_multiplication(comp->m.color, comp->light.color);
	effective_color
		= vec3_double_multiplication(effective_color, comp->light.brightness);
	light_vector
		= vec3_normalise(vec3_vec_substraction(comp->light.pos, comp->point));
	ambient = vec3_vec_multiplication(effective_color, comp->m.ambient_color);
	ambient = vec3_double_multiplication(ambient, comp->m.ambient);
	if (in_shadow)
		return (ambient);
	else
		return (
			get_lighting_extra(comp, light_vector, effective_color, ambient));
}
