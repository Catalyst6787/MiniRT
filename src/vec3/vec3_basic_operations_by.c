
#include "minirt.h"

int	vec3_substract_by_inplace(t_vec3 *vec_value, const double to_subtract)
{
	if (!vec_value || !to_subtract)
		return (ft_printf("vec3_substract_by. Error, passed NULL pointer\n"), 1);
	vec_value->x -= to_subtract;
	vec_value->y -= to_subtract;
	vec_value->z -= to_subtract;
	return (0);
}

int	vec3_add_by_inplace(t_vec3 *vec_value, const double to_add)
{
	if (!vec_value || !to_add)
		return (ft_printf("vec3_add_by. Error, passed NULL pointer\n"), 1);
	vec_value->x += to_add;
	vec_value->y += to_add;
	vec_value->z += to_add;
	return (0);
}

int	vec3_multiply_by_inplace(t_vec3 *vec_value, const double to_multiply_by)
{
	assert(vec_value);
	if (!vec_value)
		return (ft_printf("vec3_multiply_by. Error, passed NULL pointer\n"), 1);
	vec_value->x *= to_multiply_by;
	vec_value->y *= to_multiply_by;
	vec_value->z *= to_multiply_by;
	return (0);
}

int	vec3_divide_by_inplace(t_vec3 *vec_value, const double to_divide_by)
{
	if (!vec_value || !to_divide_by)
		return (ft_printf("vec3_divide_by. Error, passed NULL pointer\n"), 1);
	if (to_divide_by == 0)
		return (ft_printf("vec3_divide_by_inplace. Error, divide by zero\n"), 1);
	vec_value->x /= to_divide_by;
	vec_value->y /= to_divide_by;
	vec_value->z /= to_divide_by;
	return (0);
}
