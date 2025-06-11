#ifndef TEST_H
# define TEST_H

# include "minirt.h"
# include "matrice.h"

int			start_all_tests(void);
int			test_tuple_point(void);
int			test_tuple_vector(void);
int			test_adding_tuples(void);
int			test_subtraction_tuples(void);
int			test_scalar_multiplication(void);
int			test_scalar_division(void);
int			test_vec_normalize(void);

int			start_sphere_tests();

t_matrix	get_arb_matrix(int row, int col,
				double a0, double a1, double a2, double a3,
				double b0, double b1, double b2, double b3,
				double c0, double c1, double c2, double c3,
				double d0, double d1, double d2, double d3);



void		test_color_mult(t_vec3 *color, int i, int j);
int			start_all_matrix_tests(void);

#endif
