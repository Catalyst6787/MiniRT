
#include "minirt.h"

int	vec3_reverse_inplace(t_vec3 *vec_to_rev)
{
	if (!vec_to_rev)
		return (ft_printf("vec3_reverse. Error, passed NULL pointer\n"), 1);
	vec_to_rev->x = -vec_to_rev->x;
	vec_to_rev->y = -vec_to_rev->y;
	vec_to_rev->z = -vec_to_rev->z;
	return (0);
}

int	vec3_substract_inplace(t_vec3 *vec_value, const t_vec3 *to_subtract)
{
	if (!vec_value || !to_subtract)
		return (ft_printf("vec3_substract. Error, passed NULL pointer\n"), 1);
	vec_value->x -= to_subtract->x;
	vec_value->y -= to_subtract->y;
	vec_value->z -= to_subtract->z;
	return (0);
}

int	vec3_add_inplace(t_vec3 *vec_value, const t_vec3 *to_add)
{
	if (!vec_value || !to_add)
		return (ft_printf("vec3_add. Error, passed NULL pointer\n"), 1);
	vec_value->x += to_add->x;
	vec_value->y += to_add->y;
	vec_value->z += to_add->z;
	return (0);
}

int	vec3_multiply_inplace(t_vec3 *vec_value, const t_vec3 *to_multiply_by)
{
	if (!vec_value || !to_multiply_by)
		return (ft_printf("vec3_multiply. Error, passed NULL pointer\n"), 1);
	vec_value->x *= to_multiply_by->x;
	vec_value->y *= to_multiply_by->y;
	vec_value->z *= to_multiply_by->z;
	return (0);
}

int	vec3_divide_inplace(t_vec3 *vec_value, const t_vec3 *to_divide_by)
{
	if (!vec_value || !to_divide_by)
		return (ft_printf("vec3_multiply. Error, passed NULL pointer\n"), 1);
	if (to_divide_by->x == 0 || to_divide_by->y == 0 || to_divide_by->z == 0)
		return (ft_printf("vec3_divide_inplace. Error, divide by zero\n"), 1);
	vec_value->x /= to_divide_by->x;
	vec_value->y /= to_divide_by->y;
	vec_value->z /= to_divide_by->z;
	return (0);
}

