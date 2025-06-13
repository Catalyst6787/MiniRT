#ifndef VEC3_H
# define VEC3_H

# include "minirt.h"
// # include "matrice.h"
// # include <stdbool.h>

typedef union s_vec3
{
	struct
	{
		double	x;
		double	y;
		double	z;
		int		w;
	};
	struct
	{
		double	r;
		double	g;
		double	b;
	};
}	t_vec3;


/*                                 BASIC OPS                                  */


t_vec3	vec3_reverse(t_vec3 vec);
t_vec3	get_vec3(double x, double y, double z);
t_vec3	get_point3(double x, double y, double z);
t_vec3	vec3_dup(t_vec3 to_dup);

int		set_color(t_vec3 *v, double r, double g, double b);
t_vec3	get_color(double r, double g, double b);

t_vec3	vec3_vec_addition(char *file, int line, t_vec3 v1,t_vec3 v2);
t_vec3	vec3_vec_substraction(const t_vec3 v1,const t_vec3 v2);
t_vec3	vec3_vec_multiplication(t_vec3 v1,t_vec3 v2);
t_vec3	vec3_vec_division(t_vec3 v1,t_vec3 v2);
t_vec3	vec3_double_multiplication(t_vec3 src, double n);
t_vec3	vec3_double_division(t_vec3 src, double n);

/*                                 COMPLEX OPS                              */

double	vec3_length_squared(t_vec3 *vec3);
double	vec3_exact_length(t_vec3 *vec3);
t_vec3	vec3_normalise(t_vec3 vec3);
double	vec3_dot(const t_vec3 *vec3_u, const t_vec3 *vec3_v);
int		vec3_isequal(const t_vec3 vec3_a, const t_vec3 vec3_b);
t_vec3	vec3_cross(const t_vec3 vec3_a, const t_vec3 vec3_b);

/*                                 UTILS                                  */

int		vec3_debug_print(t_vec3	vec3);

#endif
