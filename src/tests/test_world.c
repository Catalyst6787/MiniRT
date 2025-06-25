#include "matrice.h"
#include "minirt.h"
#include "vec3.h"
#include <assert.h>



int start_all_world_tests(void)
{
	t_inter_list	inter_list;
	t_scene			scene;
	t_comp			comp;
	t_ray			r;
	t_vec3			c;
	t_ray			original_ray;
	t_view			view;
	t_matrix		orientation;

	ft_memset(&scene, 0, sizeof(t_scene));
	scene.spheres = malloc(sizeof(t_sphere) * 2);
	scene.nb_sphere = 2;
	scene.nb_objects = 2;
	scene.light = new_light(get_point3(-10, 10, -10), get_color(1, 1, 1));
	scene.spheres[0] = new_sphere(get_point3(0, 0, 0), 1, get_color(0.8, 1.0, 0.6));
	scene.spheres[1] = new_sphere(get_point3(0, 0, 0), 1, get_color(1, 1, 1));
	scene.spheres[0]->material = get_default_material(get_color(0.8, 1.0, 0.6), &scene);
	scene.spheres[1]->material = get_default_material(get_color(1, 1, 1), &scene);
	scene.spheres[0]->material.diffuse = 0.7;
	scene.spheres[0]->material.specular = 0.2;
	scene.spheres[1]->transform = get_scaling_matrix(get_vec3(0.5, 0.5, 0.5));
	scene.spheres[1]->inv = get_inversed_matrix(scene.spheres[1]->transform);
	scene.camera = new_camera(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	scene.objects = malloc(sizeof(t_object) * 2);
	create_object_list(&scene);
	r = get_ray(scene.camera->pos, scene.camera->dir);
	inter_list.capacity = 4;
	inter_list.inters = malloc(sizeof(t_inter) * inter_list.capacity);


	////////////	Test Computation outside


	inter_list.count = 0;
	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
	r = ray_transform(original_ray, scene.objects[0].inv);
	get_sphere_inter(&scene.objects[0], r, &inter_list);
	r = ray_transform(original_ray, scene.objects[1].inv);
	get_sphere_inter(&scene.objects[1], r, &inter_list);
	sort_inter(&inter_list);

	inter_list.inters[0].t = 4;
	set_computations(&comp, &scene, &inter_list.inters[0], original_ray);

	assert(comp.t == 4);
	assert(vec3_isequal(comp.point, get_point3(0, 0, -1)));
	assert(vec3_isequal(comp.eyev, get_vec3(0, 0, -1)));
	assert(vec3_isequal(comp.normalv, get_vec3(0, 0, -1)));
	assert(comp.inside == 0);


	////////////	Test Computation inside

	inter_list.count = 0;
	original_ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	r = ray_transform(original_ray, scene.objects[0].inv);
	get_sphere_inter(&scene.objects[0], r, &inter_list);
	r = ray_transform(original_ray, scene.objects[1].inv);
	get_sphere_inter(&scene.objects[1], r, &inter_list);

	inter_list.inters[0].t = 1;
	set_computations(&comp, &scene, &inter_list.inters[0], original_ray);

	assert(comp.t == 1);
	assert(vec3_isequal(comp.point, get_point3(0, 0, 1)));
	assert(vec3_isequal(comp.eyev, get_vec3(0, 0, -1)));
	assert(vec3_isequal(comp.normalv, get_vec3(0, 0, -1)));
	assert(comp.inside == 1);


	////////////	Test Shading outside


	inter_list.count = 0;
	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
	r = ray_transform(original_ray, scene.objects[0].inv);
	get_sphere_inter(&scene.objects[0], r, &inter_list);
	r = ray_transform(original_ray, scene.objects[1].inv);
	get_sphere_inter(&scene.objects[1], r, &inter_list);
	sort_inter(&inter_list);

	set_computations(&comp, &scene, &inter_list.inters[0], original_ray);
	c = get_lighting(comp, 0);
	assert(vec3_isequal(c, get_vec3(0.38066, 0.47583, 0.2855)));


	////////////	Test Shading inside



	inter_list.count = 0;
	scene.light->pos = get_point3(0, 0.25, 0);
	scene.light->color = get_color(1, 1, 1);
	original_ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	r = ray_transform(original_ray, scene.objects[0].inv);
	get_sphere_inter(&scene.objects[0], r, &inter_list);
	r = ray_transform(original_ray, scene.objects[1].inv);
	get_sphere_inter(&scene.objects[1], r, &inter_list);
	sort_inter(&inter_list);
	inter_list.inters[0].obj = &scene.objects[1];
	// scene.spheres[1]->color = get_color(1, 1, 1);
	inter_list.inters[0].t = 0.5;
	set_computations(&comp, &scene, &inter_list.inters[0], original_ray);
	comp.t = 0.5;
	c = get_lighting(comp, 0);
	assert(vec3_isequal(c, get_vec3(0.90498, 0.90498, 0.90498)));


	////////////	Test if color missing or not

	inter_list.count = 0;
	original_ray = get_ray(get_point3(0, 0, -5), get_vec3(0, 1 ,0));
	r = ray_transform(original_ray, scene.objects[0].inv);
	get_sphere_inter(&scene.objects[0], r, &inter_list);
	r = ray_transform(original_ray, scene.objects[1].inv);
	get_sphere_inter(&scene.objects[1], r, &inter_list);
	sort_inter(&inter_list);

	if (inter_list.count)
	{
		set_computations(&comp, &scene, &inter_list.inters[0], original_ray);
		c = get_lighting(comp, 0);
	}
	else
		c = get_color(0, 0, 0); //should we add bakcground colour to the scene ?
	assert(vec3_isequal(c, get_vec3(0, 0, 0)));


	////////////	Intersection behind the ray

	scene.objects[0].material.ambient = 1;
	scene.objects[1].material.ambient = 1;
	original_ray = get_ray(get_point3(0, 0, 0.75), get_vec3(0, 0 ,-1));
	set_computations(&comp, &scene, &inter_list.inters[0], original_ray);
	c = get_lighting(comp, 0);
	assert(vec3_isequal(c, scene.objects[1].material.color));

	//// transformation matrix for default orientation

	view.from = get_point3(0, 0, 0);
	view.to = get_point3(0, 0, -1);
	view.up = get_vec3(0, 1, 0);
	orientation = get_orientation_matrix(view);
	assert(matrix_isequal(orientation, get_matrix(4, 4, 1)));


	//// transformation matrix looking in pos z dir

	view.from = get_point3(0, 0, 0);
	view.to = get_point3(0, 0, 1);
	view.up = get_vec3(0, 1, 0);
	orientation = get_orientation_matrix(view);
	assert(matrix_isequal(orientation, get_scaling_matrix(get_vec3(-1, 1, -1))));


	////////////	Transformation matrix for arbitrary orientation

	t_matrix result = get_arb_matrix(4, 4,
				-0.50709, 0.50709, 0.67612, -2.36643,
				0.76772, 0.60609, 0.12122, -2.82843,
				-0.35857, 0.59761, -0.71714, 0.00000,
				0.00000, 0.00000, 0.00000, 1.00000);

	view.from = get_point3(1, 3, 2);
	view.to = get_point3(4, -2, 8);
	view.up = get_vec3(1, 1, 0);
	orientation = get_orientation_matrix(view);
	assert(matrix_isequal(orientation, result));




	////////////	Free


	free(scene.light);
	free(inter_list.inters);
	// free_sphere(&scene.objects[0]);
	// free_sphere(&scene.objects[1]);
	free(scene.objects);
	free(scene.camera);
	return (0);
}
