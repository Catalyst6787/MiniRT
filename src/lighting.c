#include "minirt.h"

t_light	get_light(t_vec3 pos, double brightness, t_vec3 color)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	light.color = color;
	return (light);
}

t_vec3	get_lighting(t_lighting	lighting)
{
	t_vec3	effective_color;
	t_vec3	light_vector;
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	t_vec3	reflectv;
	double	light_dot_normal;
	double	reflect_dot_eye;
	double	factor;

	effective_color = vec3_vec_multiplication(lighting.m.color, lighting.light.color);
	effective_color = vec3_double_multiplication(effective_color, lighting.light.brightness);
	light_vector = vec3_normalise(vec3_vec_substraction(lighting.light.pos, lighting.pos));
	ambient = vec3_vec_multiplication(effective_color, lighting.m.ambient_color);
	ambient = vec3_double_multiplication(ambient, lighting.m.ambient);
	light_dot_normal = vec3_dot(&light_vector, &lighting.normalv);
	if (light_dot_normal < 0)
	{
		diffuse = get_color(0, 0, 0);
		specular = get_color(0, 0, 0);
	}
	else
	{
		diffuse = vec3_double_multiplication(effective_color, (lighting.m.diffuse * light_dot_normal));
		reflectv = get_reflection(vec3_reverse(light_vector), lighting.normalv);
		reflect_dot_eye = vec3_dot(&reflectv, &lighting.eyev);
		if (reflect_dot_eye <= 0)
			specular = get_color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, lighting.m.shininess);
			specular = vec3_double_multiplication(
					vec3_double_multiplication(
						lighting.light.color,
						lighting.m.specular),
					factor);
		}
	}
	return (vec3_vec_addition(ambient, vec3_vec_addition(diffuse, specular)));
}
