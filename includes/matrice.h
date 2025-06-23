#ifndef MATRICE_H
# define MATRICE_H

#include <stdbool.h>
#include "vec3.h"

typedef struct s_matrix
{
	double	matrix[4][4];
	int		row;
	int		col;
}			t_matrix;

typedef struct s_shear
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}			t_shear;

////////		Utils

void			print_matrice(t_matrix m);
t_matrix		get_matrix(int row, int col, bool identity);
bool			matrix_isequal(t_matrix m1, t_matrix m2);
void			matrix_set_elem(t_matrix *m, int i, int j, double elem);
t_shear			get_shear_params(void);

////////		Operations

t_matrix		transpose_matrix(t_matrix m);
t_matrix		multiply_matrix(t_matrix m1, t_matrix m2);

////////		Inversion

double			get_determinant(t_matrix m);
t_matrix		get_submatrice(t_matrix m, int row, int col);
bool			matrix_is_invertible(t_matrix m);
t_matrix		get_inversed_matrix(t_matrix m);

////////		Translation
t_matrix		get_translation_matrix(t_vec3 v);

////////		Scaling
t_matrix		get_scaling_matrix(t_vec3 v);

////////		Shearing
t_matrix		get_shearing_matrix(t_shear	params);

///////			All
t_matrix		get_transformation(t_matrix translation,
					t_matrix rotation, t_matrix shearing, t_matrix scaling);


////////		Rotation
t_matrix		get_rotation_matrix_x(double r);
t_matrix		get_rotation_matrix_y(double r);
t_matrix		get_rotation_matrix_z(double r);
t_matrix		get_rotation_matrix(t_vec3 v);

/*                                 MATRIX OPS                              */
t_vec3			vec3_matrix_multiply(t_matrix m, t_vec3 v);

#endif
