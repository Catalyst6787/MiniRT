#include "minirt.h"

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
	ambient = vec3_double_multiplication(effective_color, lighting.m.ambient);
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

t_light	get_light(t_vec3 pos, double brightness, t_vec3 color)
{
	t_light	light;

	light.pos = pos;
	light.brightness = brightness;
	light.color = color;
	return (light);
}

int	start_all_lighting_tests(void)
{
	t_lighting	l;
	t_vec3		result;

	l.m = get_default_material(get_vec3(1, 1, 1));
	l.pos = get_point3(0, 0, 0);

	// Lighting with the eye between the light and the surface
	l.eyev = get_vec3(0, 0, -1);
	l.normalv = get_vec3(0, 0, -1);
	l.light = get_light(get_point3(0, 0, -10), 1, get_vec3(1, 1, 1));
	result = get_lighting(l);
	assert(vec3_isequal(result, get_color(1.9, 1.9, 1.9)));
	printf("Lighting with the eye between the light and the surface passed\n");

	// Lighting with the eye between light and surface, eye offset 45°
	l.eyev = get_vec3(0, sqrt(2)/2, sqrt(2)/2);
	l.normalv = get_vec3(0, 0, -1);
	l.light = get_light(get_point3(0, 0, -10), 1, get_vec3(1, 1, 1));
	result = get_lighting(l);
	assert(vec3_isequal(result, get_color(1.0, 1.0, 1.0)));
	printf("Lighting with the eye between light and surface, eye offset 45° passed\n");

	// Lighting with eye opposite surface, light offset 45°
	l.eyev = get_vec3(0, 0, -1);
	l.normalv = get_vec3(0, 0, -1);
	l.light = get_light(get_point3(0, 10, -10), 1, get_color(1, 1, 1));
	result = get_lighting(l);
	assert(vec3_isequal(result, get_color(0.7364, 0.7364, 0.7364)));
	printf("Lighting with eye opposite surface, light offset 45° passed\n");

	// Lighting with eye in the path of the reflection vector
	l.eyev = get_vec3(0, -sqrt(2)/2, -sqrt(2)/2);
	l.normalv = get_vec3(0, 0, -1);
	l.light = get_light(get_point3(0, 10, -10), 1, get_color(1, 1, 1));
	result = get_lighting(l);
	assert(vec3_isequal((result), get_color(1.6364, 1.6364, 1.6364)));
	printf("Lighting with eye in the path of the reflection vector passed\n");

	// Lighting with the light behind the surface
	l.eyev = get_vec3(0, 0, -1);
	l.normalv = get_vec3(0, 0, -1);
	l.light = get_light(get_point3(0, 0, 10), 1, get_color(1, 1, 1));
	result = get_lighting(l);
	assert(vec3_isequal(result, get_color(0.1, 0.1, 0.1)));
	printf("Lighting with the light behind the surface passed\n");
	return (0);
}
