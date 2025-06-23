#include "minirt.h"

// int	is_shadowed(t_scene scene, t_inter *hit, t_vec3 point)
// {
// 	t_vec3	v;
// 	double	distance;
// 	// t_vec3	direction;
// 	// t_ray	r;

// 	if (!hit)
// 		return (false);
// 	v = vec3_vec_substraction(scene.light->pos, point);
// 	distance = vec3_exact_length(v);
// 	// direction = vec3_normalise(v);
// 	// r = get_ray(point, direction);
// 	if (hit->t < distance)
// 		return (true);
// 	return (false);
// }


int	start_all_shadows_tests(void)
{
// 	t_scene			scene;
// 	t_comp			comp;
// 	t_light			*light;
// 	bool			in_shadow;
// 	t_inter_list	inter_list;
// 	t_ray			original_ray;
// 	t_ray			r;
// 	t_inter			*hit;
// 	// (void) in_shadow;

// 	inter_list.count = 0;
// 	ft_memset(&scene, 0, sizeof(t_scene));
// 	scene.objects = malloc(sizeof(t_object) * 2);
// 	scene.light = new_light(get_point3(-10, 10, -10), get_color(1, 1, 1));
// 	scene.objects[0] = new_sphere(get_point3(0, 0, 0), 1, get_color(0.8, 1.0, 0.6));
// 	scene.objects[1] = new_sphere(get_point3(0, 0, 0), 1, get_color(1, 1, 1));
// 	scene.objects[0].material = get_default_material(get_color(0.8, 1.0, 0.6), &scene);
// 	scene.objects[1].material = get_default_material(get_color(1, 1, 1), &scene);
// 	scene.objects[0].material.diffuse = 0.7;
// 	scene.objects[0].material.specular = 0.2;
// 	scene.objects[1].transform = get_scaling_matrix(get_vec3(0.5, 0.5, 0.5));
// 	scene.objects[1].inv = get_inversed_matrix(scene.objects[1].transform);
// 	scene.camera = new_camera(get_point3(0, 0, -5), get_vec3(0, 0, 1));

// 	inter_list.capacity = 4;
// 	inter_list.inters = malloc(sizeof(t_inter) * inter_list.capacity);

// 	inter_list.count = 0;
// 	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
// 	r = ray_transform(original_ray, scene.objects[0].inv);
// 	get_sphere_inter(&scene.objects[0], r, &inter_list);
// 	r = ray_transform(original_ray, scene.objects[1].inv);
// 	get_sphere_inter(&scene.objects[1], r, &inter_list);
// 	sort_inter(&inter_list);

// 	inter_list.count = 0;
// 	light = new_light(get_point3(0, 0, -10), get_color(1, 1, 1));
// 	comp.eyev = get_vec3(0, 0, -1);
// 	comp.normalv = get_vec3(0, 0, -1);
// 	comp.light = *light;
// 	in_shadow = true;
// 	print_vec3(get_lighting(comp), "Lightning");
// 	hit = get_hit(&inter_list);
// 	in_shadow = is_shadowed(scene, hit, r.origin);
// 	assert(in_shadow);

	return (0);
}