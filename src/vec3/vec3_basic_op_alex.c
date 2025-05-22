
#include "minirt.h"


/*************** SETERS | GETERS ****************/

int	set_vec3(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (0);
}

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
	return (0);
}

t_vec3	get_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}


/************** 2 VECORS OPERATIONS ****************/


t_vec3	vec3_vec_addition(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec3	vec3_vec_substraction(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec3	vec3_vec_multiplication(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec3	vec3_vec_division(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}


/************** VECTOR INT OPERATIONS ****************/


t_vec3	vec3_int_addition(t_vec3 src, int n)
{
	t_vec3 v;

	v.x = src.x + n;
	v.y = src.y + n;
	v.z = src.z + n;
	return (v);

}

t_vec3	vec3_int_subtraction(t_vec3 src, int n)
{
	t_vec3 v;

	v.x = src.x - n;
	v.y = src.y - n;
	v.z = src.z - n;
	return (v);

}

t_vec3	vec3_int_multiplication(t_vec3 src, int n)
{
	t_vec3 v;

	v.x = src.x * n;
	v.y = src.y * n;
	v.z = src.z * n;
	return (v);

}

t_vec3	vec3_int_division(t_vec3 src, int n)
{
	t_vec3 v;

	v.x = src.x / n;
	v.y = src.y / n;
	v.z = src.z / n;
	return (v);
}


/************** VECTOR DOUBLE OPERATIONS ****************/


t_vec3	vec3_double_addition(t_vec3 src, double n)
{
	t_vec3 v;

	v.x = src.x + n;
	v.y = src.y + n;
	v.z = src.z + n;
	return (v);
}

t_vec3	vec3_double_substraction(t_vec3 src, double n)
{
	t_vec3 v;

	v.x = src.x - n;
	v.y = src.y - n;
	v.z = src.z - n;
	return (v);
}

t_vec3	vec3_double_multiplication(t_vec3 src, double n)
{
	t_vec3 v;

	v.x = src.x * n;
	v.y = src.y * n;
	v.z = src.z * n;
	return (v);
}

t_vec3	vec3_double_division(t_vec3 src, double n)
{
	t_vec3 v;

	v.x = src.x / n;
	v.y = src.y / n;
	v.z = src.z / n;
	return (v);
}
