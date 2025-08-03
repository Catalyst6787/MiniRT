#include "minirt.h"

int	set_color(t_vec3 *v, double r, double g, double b)
{
	v->r = r;
	v->g = g;
	v->b = b;
	return (0);
}

t_vec3	get_color(double r, double g, double b)
{
	t_vec3	c;

	c.r = r;
	c.b = b;
	c.g = g;
	c.w = 0;
	return (c);
}

t_vec3	get_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}

t_vec3	get_point3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1;
	return (v);
}
