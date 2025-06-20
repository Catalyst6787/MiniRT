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
	light->brightness = 1;
	return (light);
}

t_ambient	*new_ambiant(t_vec3 color)
{
	t_ambient	*ambient;

	ambient = ft_calloc(1, sizeof(t_ambient));
	if (!ambient)
		return (perror("new_ambient. Error\n"), NULL);
	ambient->color.x = color.x;
	ambient->color.y = color.y;
	ambient->color.z = color.z;
	ambient->brightness = 0;
	return (ambient);
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
	comp.object = (void *)hit->obj;
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
	t_view			view;
	t_matrix		orientation;

	ft_memset(&scene, 0, sizeof(t_scene));
	scene.spheres = malloc(sizeof(t_sphere) * 2);
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

	r = get_ray(scene.camera->pos, scene.camera->dir);
	inter_list.capacity = 4;
	inter_list.inters = malloc(sizeof(t_inter) * inter_list.capacity);
	
	
	////////////	Test Computation outside
	

	inter_list.count = 0;
	original_ray = get_ray(scene.camera->pos, scene.camera->dir);
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	sort_inter(&inter_list);

	inter_list.inters[0].t = 4; 
	comp = get_computations(&scene, &inter_list.inters[0], original_ray);

	assert(comp.t == 4);
	assert(vec3_isequal(comp.point, get_point3(0, 0, -1)));
	assert(vec3_isequal(comp.eyev, get_vec3(0, 0, -1)));
	assert(vec3_isequal(comp.normalv, get_vec3(0, 0, -1)));
	assert(comp.inside == 0);


	////////////	Test Computation inside

	inter_list.count = 0;
	original_ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);

	inter_list.inters[0].t = 1;
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
	sort_inter(&inter_list);

	comp = get_computations(&scene, &inter_list.inters[0], original_ray);
	c = shade_hit(comp);
	assert(vec3_isequal(c, get_vec3(0.38066, 0.47583, 0.2855)));


	////////////	Test Shading inside

	
	inter_list.count = 0;
	scene.light->pos = get_point3(0, 0.25, 0);
	scene.light->color = get_color(1, 1, 1);
	original_ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	sort_inter(&inter_list);
	inter_list.inters[0].obj = (void *)scene.spheres[1];
	// scene.spheres[1]->color = get_color(1, 1, 1);
	inter_list.inters[0].t = 0.5;
	comp = get_computations(&scene, &inter_list.inters[0], original_ray);
	comp.t = 0.5;
	c = shade_hit(comp);
	assert(vec3_isequal(c, get_vec3(0.90498, 0.90498, 0.90498)));


	////////////	Test if color missing or not


	inter_list.count = 0;
	original_ray = get_ray(get_point3(0, 0, -5), get_vec3(0, 1 ,0));
	r = ray_transform(original_ray, scene.spheres[0]->inv);
	get_sphere_inter(scene.spheres[0], r, &inter_list);
	r = ray_transform(original_ray, scene.spheres[1]->inv);
	get_sphere_inter(scene.spheres[1], r, &inter_list);
	sort_inter(&inter_list);
	
	if (inter_list.count)
	{
		comp = get_computations(&scene, &inter_list.inters[0], original_ray);
		c = shade_hit(comp);
	}
	else
		c = get_color(0, 0, 0); //should we add bakcground colour to the scene ?
	assert(vec3_isequal(c, get_vec3(0, 0, 0)));


	////////////	Intersection behind the ray


	scene.spheres[0]->material.ambient = 1;
	scene.spheres[1]->material.ambient = 1;
	original_ray = get_ray(get_point3(0, 0, 0.75), get_vec3(0, 0 ,-1));
	comp = get_computations(&scene, &inter_list.inters[0], original_ray);
	c = shade_hit(comp);
	assert(vec3_isequal(c, scene.spheres[1]->material.color));


	////////////	Trnsformation matrix for default orientation

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
	free_sphere(scene.spheres[0]);
	free_sphere(scene.spheres[1]);
	free(scene.spheres);
	free(scene.camera);
	return (0);
}
