#include "minirt.h"

int	vec3_isequal(const t_vec3 vec3_a, const t_vec3	vec3_b)
{
	if (double_isequal(vec3_a.x, vec3_b.x)
		&& double_isequal(vec3_a.y, vec3_b.y)
		&& double_isequal(vec3_a.z, vec3_b.z)
		&& double_isequal(vec3_a.w, vec3_b.w))
		return (1);
	return (0);
}

t_vec3	vec3_double_multiplication(t_vec3 src, double n)
{
	t_vec3	v;

	if (src.w)
		print_err(FILE, LINE,
			"vec3_double_multiplication, trying to multiply a point");
	v.x = src.x * n;
	v.y = src.y * n;
	v.z = src.z * n;
	v.w = src.w;
	return (v);
}

t_vec3	vec3_double_division(t_vec3 src, double n)
{
	t_vec3	v;

	if (src.w)
		print_err(FILE, LINE,
			"vec3_double_division, trying to multiply a point");
	v.x = src.x / n;
	v.y = src.y / n;
	v.z = src.z / n;
	v.w = src.w;
	return (v);
}

t_vec3	vec3_reverse(t_vec3 vec)
{
	if (vec.w)
		print_err(FILE, LINE, "vec3_reverse, trying to reverse a point");
	return (get_vec3(-vec.x, -vec.y, -vec.z));
}

t_vec3	vec3_dup(t_vec3 to_dup)
{
	t_vec3	vec3;

	vec3.x = to_dup.x;
	vec3.y = to_dup.y;
	vec3.z = to_dup.z;
	vec3.w = to_dup.w;
	return (vec3);
}
