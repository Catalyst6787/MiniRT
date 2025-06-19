#include "minirt.h"

t_light	*new_light(t_vec3 pos, t_vec3 color)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (perror("new_light. Error\n"), NULL);
	light->pos.x = pos.x;
	light->pos.y = pos.y;
	light->pos.z = pos.z;
	light->pos.w = 1;
	light->color.x = color.x;
	light->color.y = color.y;
	light->color.z = color.z;
	return (light);
}

t_camera	*new_camera(t_vec3 pos, t_vec3 dir)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (perror("new_camera. Error\n"), NULL);
	camera->pos.x = pos.x;
	camera->pos.y = pos.y;
	camera->pos.z = pos.z;
	camera->pos.w = 1;
	camera->dir.x = dir.x;
	camera->dir.y = dir.y;
	camera->dir.z = dir.z;
	camera->dir.w = 0;
	return (camera);
}

int	intersect_test(t_scene scene)
{
	(void) scene;

	return (0);
}

t_comp	get_computations(t_scene *scene, t_inter *hit, t_ray r) // need to replace sphere by object
{
	t_comp		comp;
	const t_sphere	*sphere; // change for object

	ft_memset(&comp, 0, sizeof(comp));
	comp.eyev =  vec3_reverse(r.dir);
	comp.light = *scene->light;
	sphere = (t_sphere *)hit->obj;
	comp.m = sphere->material;
	comp.point = ray_at(hit->t, r);
	comp.normalv = get_sphere_normal_at(hit->obj, comp.point);
	comp.t = hit->t;
	if (vec3_dot(&comp.normalv, &comp.eyev) < 0)
	{
		comp.inside = true;
		comp.normalv = vec3_reverse(comp.normalv);
	}
	else
		comp.inside = false;
	return (comp);
}

t_vec3	shade_hit(t_comp comp)
{
// 	(void)inter_list;
	t_vec3	color;

	color = get_lighting(comp);
	return (color);
}

int start_all_world_tests(void)
{
	t_inter_list	inter_list;
	t_scene			scene;
	t_comp			comp;
	t_ray			r;
	t_vec3			c;
	t_ray			original_ray;


	scene.spheres = malloc(sizeof(t_sphere) * 2);
	scene.light = new_light(get_point3(-10, 10, -10), get_color(1, 1, 1));
	scene.spheres[0] = new_sphere(get_point3(0, 0, 0), 1, get_color(0.8, 1.0, 0.6));
	scene.spheres[1] = new_sphere(get_point3(0, 0, 0), 1, get_color(1, 0.2, 0.1));
	scene.spheres[0]->material.diffuse = 0.7;
	scene.spheres[0]->material.specular = 0.2;
	scene.spheres[1]->transform = get_scaling_matrix(get_vec3(0.5, 0.5, 0.5));
	scene.spheres[1]->inv = get_inversed_matrix(scene.spheres[1]->transform);
	scene.camera = new_camera(get_point3(0, 0, -5), get_vec3(0, 0, 1));

	r = get_ray(scene.camera->pos, scene.camera->dir);
	inter_list.capacity = 4;
	inter_list.inters = malloc(sizeof(t_inter) * inter_list.capacity);
	
	////////////	Test Computation outside
	
	// printf("\nOutside computation :\n\n");
	inter_list.count = 0;
	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("xs[%d].t = %.2f\n", i, inter_list.inters[i].t);
	sort_inter(&inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("sorted xs[%d].t = %.2f\n", i, inter_list.inters[i].t);

	comp = get_computations(&scene, &inter_list.inters[0], original_ray);

	assert(comp.t == 4);
	assert(vec3_isequal(comp.point, get_point3(0, 0, -1)));
	assert(vec3_isequal(comp.eyev, get_vec3(0, 0, -1)));
	assert(vec3_isequal(comp.normalv, get_vec3(0, 0, -1)));
	assert(comp.inside == 0);

	////////////	Test Computation inside

	// printf("\nInside computation :\n\n");
	inter_list.count = 0;
	original_ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("xs[%d].t = %.2f\n", i, inter_list.inters[i].t);
	sort_inter(&inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("sorted xs[%d].t = %.2f\n", i, inter_list.inters[i].t);

	inter_list.inters[0].t = 1; //delete and rearrange inter for when the ray is inside an object
	comp = get_computations(&scene, &inter_list.inters[0], original_ray);

	assert(comp.t == 1);
	assert(vec3_isequal(comp.point, get_point3(0, 0, 1)));
	assert(vec3_isequal(comp.eyev, get_vec3(0, 0, -1)));
	assert(vec3_isequal(comp.normalv, get_vec3(0, 0, -1)));
	assert(comp.inside == 1);


	////////////	Test Shading outside

	(void)c;
	inter_list.count = 0;
	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("xs[%d].t = %.2f\n", i, inter_list.inters[i].t);
	sort_inter(&inter_list);
	// for (int i = 0; i < 4; i++)
	// 	printf("sorted xs[%d].t = %.2f\n", i, inter_list.inters[i].t);

	comp = get_computations(&scene, &inter_list.inters[0], original_ray);

	c = shade_hit(comp);
	// print_vec3(c, "color");

	// if (!comp.inside)
	// {
	// }



	// scene.light = new_light(get_point3(0, 0.25, 0), get_color(1, 1, 1));
	// r = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	
	// assert(vec3_isequal(c, get_color(0.38066, 0.47583, 0.2855)));
	




	free(scene.light);
	free(inter_list.inters);
	free_sphere(scene.spheres[0]);
	free_sphere(scene.spheres[1]);
	free(scene.spheres);
	free(scene.camera);
	return (0);
}
