#include "errors.h"
#include "libft.h"
#include "matrice.h"
#include "minirt.h"
#include "object.h"
#include "ray.h"
#include "render.h"
#include "scene.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>

int	basic_test_reflection(void)
{
	t_vec3	v;
	t_vec3	n;
	t_vec3	r;

	v = get_vec3(1, -1, 0);
	n = get_vec3(0, 1, 0);
	r = get_reflection(v, n);
	assert(vec3_isequal(r, get_vec3(1, 1, 0)));
	return (0);
}

int	test_slanted_reflection(void)
{
	t_vec3	v;
	t_vec3	n;
	t_vec3	r;

	v = get_vec3(0, -1, 0);
	n = get_vec3(sqrt(2) / 2, sqrt(2) / 2, 0);
	r = get_reflection(v, n);
	assert(vec3_isequal(r, get_vec3(1, 0, 0)));

	return (0);
}

// int	strike_surface_test(void)
// {
// 	t_minirt			minirt;
// 	t_render			render;
// 	t_scene				scene;
// 	t_ray					r;
// 	t_object			shape;
// 	t_inter				*hit;
// 	t_inter_list	inter_lst;
// 	t_comp				comp;
// 	t_vec3				color;
// 	t_plane				*plane;

// 	ft_memset(&scene, 0, sizeof(t_scene));
// 	inter_lst.inters = malloc(sizeof(t_inter) * 10);
// 	inter_lst.capacity = 9;
// 	inter_lst.count = 0;

// 	// strike a non_reflective surface :
// 	set_default_world(&scene);
// 	r = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
// 	shape = scene.objects[1];
// 	shape.material.ambient = 1;
// 	get_intersection(&shape, &r, &inter_lst);
// 	hit = get_hit(&inter_lst);
// 	set_computations(&comp, scene.lights[0], hit, &r);
// 	color = reflected_color(&comp, &);
// 	color = get_vec3(0, 0, 0);
// 	assert(vec3_isequal(color, get_vec3(0, 0, 0)));


// 	inter_lst.count = 0;
// 	plane = new_plane(get_point3(0, -1, 0), get_vec3(0, 1, 0), get_color(1, 1, 1));
// 	create_object_from_plane(&shape, plane, 0);
// 	shape.material = get_default_material(get_color(0, 0, 0), &scene);
// 	shape.material.reflective = 0.5;
// 	shape.transform = get_translation_matrix(get_vec3(0, -1, 0));
// 	scene.objects[3] = shape;
// 	scene.nb_objects = 3;
// 	r = get_ray(get_point3(0, 0, -3), get_vec3(0, -sqrt(2)/2, sqrt(2)/2));
// 	hit->obj = &shape;
// 	hit->t = sqrt(2);
// 	set_computations(&comp, scene.lights[0], hit, &r);
// 	color = reflected_color(&comp, &scene);
// 	assert(vec3_isequal(color, get_vec3(0.19032, 0.2379, 0.14274)));
	
// 	free_scene(&scene);
// 	free(inter_lst.inters);
// 	return (0);
// }

int	start_all_reflection_tests(void)
{
	basic_test_reflection();
	printf("basic_test_reflection passed\n");
	test_slanted_reflection();
	printf("test_slanted_reflection passed\n");
	// strike_surface_test();
	// printf("strike surface test passed\n");
	return (0);
}
