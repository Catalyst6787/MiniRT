
#include "minirt.h"

t_vec3	vec3_reverse(t_vec3 vec)
{
	if (vec.w)
		print_err(FILE, LINE, "vec3_reverse, trying to reverse a point");
	return (get_vec3(-vec.x, -vec.y, -vec.z, vec.w));
}

/*************** SETERS | GETERS ****************/

// int	set_vec3(t_vec3 *v, double x, double y, double z)
// {
// 	v->x = x;
// 	v->y = y;
// 	v->z = z;
// 	v->w = 0;
// 	return (0);
// }

// int	set_point3(t_vec3 *v, double x, double y, double z)
// {
// 	v->x = x;
// 	v->y = y;
// 	v->z = z;
// 	v->w = 1;
// 	return (0);
// }

int	set_color(t_vec3 *v, double r, double g, double b)
{
	v->r = r;
	v->g = g;
	v->b = b;
	return (0);
}

int	copy_vec3(t_vec3 *dest, t_vec3 *src)
{
	if (!src)
		return (ft_printf("vec3_copy. Error, passed NULL ptr.\n"), 1);
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
	dest->w = src->w;
	return (0);
}

t_vec3	get_vec3(double x, double y, double z, int w)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
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


/************** 2 VECORS OPERATIONS ****************/


t_vec3	vec3_vec_addition(char *file, int line, t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;
	(void)file;
	(void)line;

	if (v1.w && v2.w)
		print_err(file, line, "vec3_vec_addition, trying to add two points");
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
		print_err(FILE, LINE, "vec3_vec_substraction, trying to substract a point from a vec");
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec3	vec3_vec_multiplication(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	if (v1.w || v1.w)
		print_err(FILE, LINE, "vec3_vec_multiplication, trying to multiply a point");
	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec3	vec3_vec_division(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	if (v1.w || v1.w)
		print_err(FILE, LINE, "vec3_vec_division, trying to multiply a point");
	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}


/************** VECTOR INT OPERATIONS ****************/


// t_vec3	vec3_int_addition(t_vec3 src, int n)
// {
// 	t_vec3 v;

// 	v.x = src.x + n;
// 	v.y = src.y + n;
// 	v.z = src.z + n;
// 	return (v);

// }

// t_vec3	vec3_int_subtraction(t_vec3 src, int n)
// {
// 	t_vec3 v;

// 	v.x = src.x - n;
// 	v.y = src.y - n;
// 	v.z = src.z - n;
// 	return (v);

// }

t_vec3	vec3_int_multiplication(t_vec3 src, int n)
{
	t_vec3 v;

	if (src.w)
		print_err(FILE, LINE, "vec3_int_multiplication, trying to multiply a point");
	v.x = src.x * n;
	v.y = src.y * n;
	v.z = src.z * n;
	return (v);

}

t_vec3	vec3_int_division(t_vec3 src, int n)
{
	t_vec3 v;

	if (src.w)
		print_err(FILE, LINE, "vec3_int_division, trying to divide a point");
	v.x = src.x / n;
	v.y = src.y / n;
	v.z = src.z / n;
	return (v);
}


/************** VECTOR DOUBLE OPERATIONS ****************/


// t_vec3	vec3_double_addition(t_vec3 src, double n)
// {
// 	t_vec3 v;

// 	v.x = src.x + n;
// 	v.y = src.y + n;
// 	v.z = src.z + n;
// 	return (v);
// }

// t_vec3	vec3_double_substraction(t_vec3 src, double n)
// {
// 	t_vec3 v;

// 	v.x = src.x - n;
// 	v.y = src.y - n;
// 	v.z = src.z - n;
// 	return (v);
// }

t_vec3	vec3_double_multiplication(t_vec3 src, double n)
{
	t_vec3 v;

	if (src.w)
		print_err(FILE, LINE, "vec3_double_multiplication, trying to multiply a point");
	v.x = src.x * n;
	v.y = src.y * n;
	v.z = src.z * n;
	return (v);
}

t_vec3	vec3_double_division(t_vec3 src, double n)
{
	t_vec3 v;

	if (src.w)
		print_err(FILE, LINE, "vec3_double_division, trying to multiply a point");
	v.x = src.x / n;
	v.y = src.y / n;
	v.z = src.z / n;
	return (v);
}
