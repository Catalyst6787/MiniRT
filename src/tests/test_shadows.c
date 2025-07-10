#include "minirt.h"

int	is_shadowed_tests(t_scene *scene, t_vec3 point)
{
	t_vec3			v;
	double			distance;
	t_vec3			direction;
	t_ray			r;
	t_inter_list	list;
	int				i;
	t_inter			*hit;


	list.capacity = 4;  //need to implement this to miniRT
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.count = 0;
	i = 0;
	v = vec3_vec_substraction(scene->light->pos, point);
	distance = vec3_exact_length(v);
	direction = vec3_normalise(v);
	r = get_ray(point, direction);
	while (i < scene->nb_objects)
	{
		get_intersection(&scene->objects[i], &r, &list);
		i++;
	}
	i = 0;
	hit = get_hit(&list);

	if (hit && hit->t < distance)
		return (free(list.inters), true);
	return (free(list.inters), false);
}

void	set_default_world(t_scene *scene)
{
	scene->light = new_light(get_point3(-10, 10, -10), get_color(1, 1, 1));
	scene->spheres = malloc(sizeof(t_sphere) * 2);
	scene->spheres[0] = new_sphere(get_point3(0, 0, 0), 1, get_color(0.8, 1.0, 0.6));
	scene->spheres[1] = new_sphere(get_point3(0, 0, 0), 1, get_color(1, 1, 1));
	scene->spheres[0]->material = get_default_material(get_color(0.8, 1.0, 0.6), scene);
	scene->spheres[1]->material = get_default_material(get_color(1, 1, 1), scene);
	scene->spheres[0]->material.diffuse = 0.7;
	scene->spheres[0]->material.specular = 0.2;
	scene->spheres[0]->transform = get_matrix(4, 4, 1);
	scene->spheres[0]->inv = get_matrix(4, 4, 1);
	scene->spheres[1]->transform = get_scaling_matrix(get_vec3(0.5, 0.5, 0.5));
	scene->spheres[1]->inv = get_inversed_matrix(scene->spheres[1]->transform);
	scene->nb_sphere = 2;
	scene->nb_objects = 2;
	scene->objects = malloc(sizeof(t_object) * 2);
	create_object_list(scene);
}

void	set_rendering_shadow_world(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->light = new_light(get_point3(0, 0, -10), get_color(1, 1, 1));
	scene->spheres = malloc(sizeof(t_sphere) * 2);
	scene->spheres[0] = new_sphere(get_point3(0, 0, 0), 1, get_color(0.8, 1.0, 0.6));
	scene->spheres[1] = new_sphere(get_point3(0, 0, 10), 1, get_color(1, 1, 1));
	scene->spheres[0]->material = get_default_material(get_color(1, 1, 1), scene);
	scene->spheres[1]->material = get_default_material(get_color(1, 1, 1), scene);
	scene->spheres[1]->transform = get_translation_matrix(get_vec3(0, 0, 10));
	scene->spheres[1]->inv = get_inversed_matrix(scene->spheres[1]->transform);
	scene->nb_sphere = 2;
	scene->nb_objects = 2;
	scene->objects = malloc(sizeof(t_object) * 2);
	create_object_list(scene);
}

// void	set_rendering_shadow_world_2(t_scene *scene)
// {
// 	ft_memset(scene, 0, sizeof(t_scene));


// }


int	start_all_shadows_tests(void)
{
	t_comp			comp;
	t_inter_list	list;
	t_vec3			color;
	bool			in_shadow;
	t_scene			scene;
	t_ray			r;
	int				i;
	t_sphere		*sphere;

	i = 0;
	ft_memset(&scene, 0, sizeof(t_scene));
	scene.nb_plane = 0;
	scene.nb_cylinder = 0;

	////////////	Tests color if shadowed

	set_default_world(&scene);
	list.count = 0;

	comp.eyev = get_vec3(0, 0, -1);
	comp.normalv = get_vec3(0, 0, -1);
	scene.light->pos = get_point3(0, 0, -10);
	scene.light->color = get_color(1, 1, 1);
	comp.light = *scene.light;
	comp.point = get_point3(0, 0, 0);  //don't know about this one

	comp.m = get_default_material(get_color(1, 1, 1), &scene);

	in_shadow = true;
	color = get_lighting(&comp, in_shadow);
	assert(vec3_isequal(color, get_vec3(0.1, 0.1, 0.1)));


	////////////	is_shadowed tests

	free(scene.light);
	free(scene.spheres[0]);
	free(scene.spheres[1]);
	free(scene.spheres);
	free(scene.objects);
	set_default_world(&scene);

	in_shadow = is_shadowed_tests(&scene, get_point3(0, 10, 0));
	assert(!in_shadow);
	in_shadow = is_shadowed_tests(&scene, get_point3(10, -10, 10));
	assert(in_shadow);
	in_shadow = is_shadowed_tests(&scene, get_point3(-20, 20, -20));
	assert(!in_shadow);
	in_shadow = is_shadowed_tests(&scene, get_point3(-2, 2, -2));
	assert(!in_shadow);

	////////////	Tests rendering shadows

	free(scene.light);
	free(scene.spheres[0]);
	free(scene.spheres[1]);
	free(scene.spheres);
	free(scene.objects);
	set_rendering_shadow_world(&scene);
	r = get_ray(get_point3(0, 0, 5), get_vec3(0, 0, 1));

	list.capacity = 4;  //need to implement this to miniRT
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.count = 0;
	while (i < scene.nb_objects)
	{
		get_intersection(&scene.objects[i], &r, &list);
		i++;
	}
	list.inters[0].obj = &scene.objects[1];
	list.inters[0].t = 4;
	set_computations(&comp, &scene, &list.inters[0], &r);
	// color = shade_hit(&scene, &comp); //this works if in_shadow is true (will be implemented later in tests) !!!
	// assert(vec3_isequal(color, get_vec3(0.1, 0.1, 0.1)));


	////////////	Tests rendering shadows 2

	(void)sphere;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	free(scene.spheres[0]);
	free(scene.spheres[1]);
	free(scene.objects);
	list.capacity = 4;
	free(list.inters);
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.count = 0;
	scene.spheres[0] = new_sphere(get_point3(0, 0, 1), 1, get_color(1, 1, 1));
	set_sphere_transformation(scene.spheres[0]);
	scene.nb_sphere = 1;
 	scene.nb_objects = 1;
	scene.objects = malloc(sizeof(t_object));
	create_object_list(&scene);

	list.inters[0].obj = scene.objects;
	list.inters[0].t = 5;

	set_computations(&comp, &scene, &list.inters[0], &r);
	assert(comp.over_point.z < (-EPSILON / 2));
	assert(comp.point.z > (comp.over_point.z));

	free(scene.spheres[0]);
	free(list.inters);
	free(scene.spheres);
	free(scene.objects);
	free(scene.light);

	return (0);
}
