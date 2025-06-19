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



int start_all_world_tests(void)
{
	t_light			*light;
	t_inter_list	i;
	t_scene			scene;
	(void) i;

	scene.spheres = malloc(sizeof(t_sphere) * 2);
	light = new_light(get_point3(-10, 10, -10), get_color(1, 1, 1));
	scene.spheres[0] = new_sphere(get_point3(0, 0, 0), 2, get_color(0.8, 1.0, 0.6));
	scene.spheres[1] = new_sphere(get_point3(1, 0, 0), 1, get_color(1, 0.2, 0.1));
	scene.spheres[0]->material.diffuse = 0.7;
	scene.spheres[0]->material.specular = 0.2;
	scene.spheres[1]->transform = get_scaling_matrix(get_vec3(0.5, 0.5, 0.5));
	scene.camera = new_camera(get_point3(0, 0, -5), get_vec3(0, 0, 1));



	// intersect_test();



	free(light);
	free_sphere(scene.spheres[0]);
	free_sphere(scene.spheres[1]);
	free(scene.spheres);
	free(scene.camera);
	return (0);
}
