#ifndef TEST_H
# define TEST_H

int			start_all_tests(void);
int			test_tuple_point(void);
int			test_tuple_vector(void);
int			test_adding_tuples(void);
int			test_subtraction_tuples(void);
int			test_scalar_multiplication(void);
int			test_scalar_division(void);
int			test_vec_normalize(void);

t_matrix	get_arb_matrix(int row, int col,
				double a0, double a1, double a2, double a3,
				double b0, double b1, double b2, double b3,
				double c0, double c1, double c2, double c3,
				double d0, double d1, double d2, double d3);

void		test_color_mult(t_vec3 *color, int i, int j);
int			start_all_matrix_tests(void);
int			start_all_ray_tests(void);
int			start_all_intersection_tests(void);
int			start_all_normals_tests(void);
int			start_all_reflection_tests(void);
int			start_all_lighting_tests(void);
int			start_all_world_tests(void);
int			start_all_shadows_tests(void);
int			start_all_camera_tests(void);
int			start_all_planes_tests(void);
int			start_all_cylinders_tests(void);
int			start_all_cones_tests(void);
int			start_all_cubes_tests(void);

#endif
