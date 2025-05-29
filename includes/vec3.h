#ifndef VEC3_H
# define VEC3_H

# include "minirt.h"
# include <stdbool.h>

typedef union s_vec3
{
	struct
	{
		double	x;
		double	y;
		double	z;
		bool	w;
	};
	struct
	{
		double	r;
		double	g;
		double	b;
	};
}	t_vec3;

/*                                 CREATE                                  */

t_vec3	*vec3_default_alloc(void);
t_vec3	*vec3_new_alloc(const double x, const double y, const double z);
t_vec3	*vec3_dup_alloc(t_vec3 *to_dup);
t_vec3	vec3_dup(t_vec3 to_dup);
int		copy_vec3(t_vec3 *dest, t_vec3 *origin);

/*                                 BASIC OPS                                  */


t_vec3	vec3_reverse(t_vec3 vec);
int		vec3_reverse_inplace(t_vec3 *vec_to_rev);
int		vec3_substract_inplace(t_vec3 *vec_value, const t_vec3 *to_subtract);
int		vec3_add_inplace(t_vec3 *vec_value, const t_vec3 *to_add);
int		vec3_multiply_inplace(t_vec3 *vec_value, const t_vec3 *to_multiply_by);
int		vec3_divide_inplace(t_vec3 *vec_value, const t_vec3 *to_divide_by);

/******************         AJOUTS ALEX            ******************/

int		set_vec3(t_vec3 *v, double x, double y, double z);
int		copy_vec3(t_vec3 *dest, t_vec3 *src);
t_vec3	get_vec3(double x, double y, double z);

int		set_color(t_vec3 *v, double r, double g, double b);

t_vec3	vec3_vec_addition(t_vec3 v1,t_vec3 v2);
t_vec3	vec3_vec_substraction(const t_vec3 v1,const t_vec3 v2);
t_vec3	vec3_vec_multiplication(t_vec3 v1,t_vec3 v2);
t_vec3	vec3_vec_division(t_vec3 v1,t_vec3 v2);
t_vec3	vec3_int_addition(t_vec3 src, int n);
t_vec3	vec3_int_subtraction(t_vec3 src, int n);
t_vec3	vec3_int_multiplication(t_vec3 src, int n);
t_vec3	vec3_int_division(t_vec3 src, int n);
t_vec3	vec3_double_addition(t_vec3 src, double n);
t_vec3	vec3_double_substraction(t_vec3 src, double n);
t_vec3	vec3_double_multiplication(t_vec3 src, double n);
t_vec3	vec3_double_division(t_vec3 src, double n);

/*                                 COMPLEX OPS                                  */

double	vec3_length_squared(t_vec3 *vec3);
double	vec3_exact_length(t_vec3 *vec3);
void	vec3_normalise_inplace(t_vec3 *vec3);
t_vec3	vec3_normalise(t_vec3 vec3);
double	vec3_dot(t_vec3 *vec3_u, t_vec3 *vec3_v);
int		vec3_isequal(t_vec3 *vec3_a, t_vec3	*vec3_b);
t_vec3	vec3_cross(t_vec3 vec3_a, t_vec3 vec3_b);

/*                                 UTILS                                  */

int		vec3_debug_print(t_vec3 *vec3);

#endif
