#include "minirt.h"

t_vec3	color_int_multiplication(t_vec3 c0, int n)
{
	return (vec3_double_multiplication(c0, n));
}

t_vec3	color_color_multiplication(t_vec3 c1, t_vec3 c2)
{
	return (vec3_vec_multiplication(c1, c2));
}

int	color_to_int(t_vec3 *color)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(color->r * 255.0);
	green = (int)(color->g * 255.0);
	blue = (int)(color->b * 255.0);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

t_vec3	int_to_color(int int_color)
{
	t_vec3	vec_color;

	vec_color.r = int_color / 256 / 256 % 256;
	vec_color.g = int_color / 256 % 256;
	vec_color.b = int_color % 256;
	vec_color.r = vec_color.r / 255;
	vec_color.g = vec_color.g / 255;
	vec_color.b = vec_color.b / 255;
	return (vec_color);
}
