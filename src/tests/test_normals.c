#include "minirt.h"

t_vec3	get_normal_at(t_sphere *s, t_vec3 point)
{
	(void)s;
	t_vec3	v;

	v.x = point.x;
	v.y = point.y;
	v.z = point.z;
	v.w = 0;
	return (v);
}


int	basic_normal_tests()
{
	t_sphere	*s;
	t_vec3		n;
	t_vec3		point;
	(void) n;

	point = get_point3(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);

	s = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));
	n = get_normal_at(s, point);
	n = vec3_normalise(vec3_vec_substraction(point, get_point3(0, 0, 0)));
	free_sphere(s);
	return (0);
}

// int	normal_translated_tests()
// {
// 	t_sphere	*s;
// 	t_vec3		n;
// 	t_vec3		point;
// 	(void)n;

// 	s = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));
// 	s->transform  = get_translation_matrix(get_vec3(0, 1, 0));
// 	set_sphere_transformation(s);
// 	point = get_point3(0, 1.70711, -0.70711);
// 	n = get_normal_at(s, point);
// 	// assert(vec3_isequal(n, get_vec3(0, 0.70711, -0.70711)));
// 	return (0);
// }

// int	normal_transformed_tests()
// {
// 	t_sphere	*s;
// 	t_vec3		n;
// 	t_matrix	m;
// 	t_vec3		point;
// 	(void)n;

// 	s = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));
// 	m = multiply_matrix(get_scaling_matrix(get_vec3(1, 0.5, 1)), get_rotation_matrix_z(M_PI / 5));
// 	s->transform = m;
// 	set_sphere_transformation(s);
// 	point = get_point3(0, sqrt(2) / 2, (sqrt(2) / 2) * (-1));
// 	m = get_inversed_matrix(m);
// 	point = vec3_matrix_multiply(m, point);
// 	print_vec3(point, "point");
// 	n = get_normal_at(s, point);
// 	return (0);
// }


int	start_all_normals_tests(void)
{
	basic_normal_tests();
	printf("basic_normal_test passed\n");
	// normal_translated_tests();
	// printf("translated_normal_test passed\n");
	// normal_transformed_tests();
	// printf("transpormed_normal_test passed\n");
	return (0);
}