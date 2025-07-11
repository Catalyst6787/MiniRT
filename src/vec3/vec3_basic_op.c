
#include "minirt.h"

t_vec3	vec3_vec_addition(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	if (v1.w && v2.w)
		print_err(FILE, LINE, "vec3_vec_addition, trying to add two points");
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	v.w = v1.w + v2.w;
	return (v);
}

t_vec3	vec3_vec_substraction(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	v;

	if (!v1.w && v2.w)
		print_err(FILE, LINE,
			"vec3_vec_substraction, trying to substract a point from a vec");
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	v.w = v1.w - v2.w;
	return (v);
}

t_vec3	vec3_vec_multiplication(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	if (v1.w || v2.w)
		print_err(FILE, LINE,
			"vec3_vec_multiplication, trying to multiply a point");
	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	v.w = 0;
	return (v);
}

t_vec3	vec3_vec_division(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	if (v1.w || v1.w)
		print_err(FILE, LINE, "vec3_vec_division, trying to multiply a point");
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	v.w = 0;
	return (v);
}
