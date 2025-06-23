#include "minirt.h"

int	basic_normal_tests(void)
{
	t_object	s;
	t_vec3		n;
	t_vec3		point;

	s = new_sphere(get_point3(0, 0, 0), 1, get_color(1, 0, 0));
	n = get_sphere_normal_at(&s, get_point3(1, 0, 0));
	assert(vec3_isequal(n, get_vec3(1, 0, 0)));
	n = get_sphere_normal_at(&s, get_point3(0, 1, 0));
	assert(vec3_isequal(n, get_vec3(0, 1, 0)));
	n = get_sphere_normal_at(&s, get_point3(0, 0, 1));
	assert(vec3_isequal(n, get_vec3(0, 0, 1)));

	point = get_point3(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);

	n = get_sphere_normal_at(&s, point);
	assert(vec3_isequal(n, get_vec3(point.x, point.y, point.z)));

	assert(vec3_isequal(n, vec3_normalise(n)));

	// free_sphere(&s);
	return (0);
}

int	advanced_normal_tests(void)
{
	t_object	s;
	t_vec3		n;

	s = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));

	// computing the normal on a translated sphere
	s.pos = get_vec3(0, 1, 0);
	set_sphere_transformation(&s);
	n = get_sphere_normal_at(&s, get_point3(0, 1.70711, -0.70711));
	assert(vec3_isequal(n, get_vec3(0, 0.70711, -0.70711)));

	// free_sphere(&s);
	s = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));
	// computing the normal on a transformed sphere
	s.transform = multiply_matrix(
			get_scaling_matrix(get_vec3(1, 0.5, 1)),
			get_rotation_matrix_z(M_PI / 5));
	s.inv = get_inversed_matrix(s.transform);
	n = get_sphere_normal_at(&s, get_point3(0, sqrt(2) / 2, -sqrt(2) / 2));
	assert(vec3_isequal(n, get_vec3(0, 0.97014, -0.24254)));

	// free_sphere(&s);
	return (0);
}

int	start_all_normals_tests(void)
{
	basic_normal_tests();
	printf("basic_normal_test passed\n");
	advanced_normal_tests();
	printf("advanced_normal_tests passed\n");
	return (0);
}
