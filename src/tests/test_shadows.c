#include "minirt.h"

int	is_shadowed(t_scene scene, t_vec3 point)
{
	t_vec3			v;
	double			distance;
	t_vec3			direction;
	t_ray			r;
	t_inter_list	list;
	int				i;
	t_inter			*hit;

	list.inters = malloc(sizeof(t_inter) * 4);
	list.capacity = 4;
	list.count = 0;
	i = 0;
	v = vec3_vec_substraction(scene.light->pos, point);
	distance = vec3_exact_length(v);
	direction = vec3_normalise(v);
	r = get_ray(point, direction);
	while (i < scene.nb_objects)
	{
		get_intersection(&scene.objects[i], r, &list);
		i++;
	}

	hit = get_hit(&list);
	if (hit && hit->t < distance)
		return (true);
	return (false);
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

int	start_all_shadows_tests(void)
{

	t_comp			comp;
	t_inter_list	inter_list;
	t_vec3			color;
	bool			in_shadow;
	t_scene			scene;

	ft_memset(&scene, 0, sizeof(t_scene));
	set_default_world(&scene);
	inter_list.count = 0;

	comp.eyev = get_vec3(0, 0, -1);
	comp.normalv = get_vec3(0, 0, -1);
	scene.light->pos = get_point3(0, 0, -10);
	scene.light->color = get_color(1, 1, 1);
	comp.light = *scene.light;
	comp.m = get_default_material(get_color(1, 1, 1), &scene);

	in_shadow = true;
	color = get_lighting(comp, in_shadow);
	assert(vec3_isequal(color, get_vec3(0.1, 0.1, 0.1)));

	set_default_world(&scene);

	in_shadow = is_shadowed(scene, get_point3(0, 10, 0));
	assert(!in_shadow);

	in_shadow = is_shadowed(scene, get_point3(10, -10, 10));
	assert(in_shadow);

	in_shadow = is_shadowed(scene, get_point3(-20, 20, -20));
	assert(!in_shadow);

	in_shadow = is_shadowed(scene, get_point3(-2, 2, -2));
	assert(!in_shadow);
	return (0);
}
