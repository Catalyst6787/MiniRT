#include "minirt.h"

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
