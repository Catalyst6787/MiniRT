#include "minirt.h"

void	scene_1(t_minirt *minirt)
{
	int	i;

	i = 0;
	free(minirt->scene->objects);
	free(minirt->render->inter_list.inters);
	minirt->scene->nb_objects = 6;
	minirt->scene->objects = malloc(sizeof(t_object) * minirt->scene->nb_objects);
	// ft_memset(&minirt->scene->objects, 0, sizeof(t_object) * minirt->scene->nb_objects);
	minirt->render->inter_list.inters = malloc(sizeof(t_inter) * minirt->scene->nb_objects * 2);
	minirt->render->inter_list.capacity = minirt->scene->nb_objects * 2;
	minirt->render->inter_list.count = 0;
	while(i < 6)
	{
		minirt->scene->objects[i].type = SPHERE;
		i++;
	}
	// floor
	minirt->scene->objects[0].transform = get_scaling_matrix(get_vec3(10, 0.01, 10));
	minirt->scene->objects[0].inv = get_inversed_matrix(minirt->scene->objects[0].transform);
	minirt->scene->objects[0].material = get_default_material(get_color(1, 1, 1), minirt->scene);
	minirt->scene->objects[0].material.specular = 0;
	// left wall
	minirt->scene->objects[1].transform = get_transformation(get_translation_matrix(get_vec3(0, 0, 5)), get_rotation_matrix(get_vec3(M_PI / 2 , -M_PI / 4, 0)), get_matrix(4, 4, true), get_scaling_matrix(get_vec3(10, 0.01, 10)));
	minirt->scene->objects[1].inv = get_inversed_matrix(minirt->scene->objects[1].transform);
	minirt->scene->objects[1].material = get_default_material(get_color(1, 0.9, 0.9), minirt->scene);
	minirt->scene->objects[1].material.specular = 0;
	// right wall
	minirt->scene->objects[2].transform = get_transformation(get_translation_matrix(get_vec3(0, 0, 5)), get_rotation_matrix(get_vec3(M_PI / 2 , M_PI / 4, 0)), get_matrix(4, 4, true), get_scaling_matrix(get_vec3(10, 0.01, 10)));
	minirt->scene->objects[2].inv = get_inversed_matrix(minirt->scene->objects[2].transform);
	minirt->scene->objects[2].material = get_default_material(get_color(1, 0.9, 0.9), minirt->scene);
	minirt->scene->objects[2].material.specular = 0;

	// large sphere
	minirt->scene->objects[3].transform = get_translation_matrix(get_vec3(-0.5, 1, 0.5));
	minirt->scene->objects[3].inv = get_inversed_matrix(minirt->scene->objects[3].transform);
	minirt->scene->objects[3].material = get_default_material(get_color(0.1, 1, 0.5), minirt->scene);
	minirt->scene->objects[3].material.specular = 0.3;
	minirt->scene->objects[3].material.diffuse 	= 0.7;

	// small sphere
	minirt->scene->objects[4].transform = get_transformation(get_translation_matrix(get_vec3(1.5, 0.5, -0.5)), get_matrix(4, 4, true), get_matrix(4, 4, true), get_scaling_matrix(get_vec3(0.5, 0.5, 0.5)));
	minirt->scene->objects[4].inv = get_inversed_matrix(minirt->scene->objects[4].transform);
	minirt->scene->objects[4].material = get_default_material(get_color(0.5, 1, 0.1), minirt->scene);
	minirt->scene->objects[4].material.specular = 0.3;
	minirt->scene->objects[4].material.diffuse 	= 0.7;

	// smallest sphere
	minirt->scene->objects[5].transform = get_transformation(get_translation_matrix(get_vec3(-1.5, 0.33, -0.75)), get_matrix(4, 4, true), get_matrix(4, 4, true), get_scaling_matrix(get_vec3(0.33, 0.33, 0.33)));
	minirt->scene->objects[5].inv = get_inversed_matrix(minirt->scene->objects[5].transform);
	minirt->scene->objects[5].material = get_default_material(get_color(1, 0.8, 0.1), minirt->scene);
	minirt->scene->objects[5].material.specular = 0.3;
	minirt->scene->objects[5].material.diffuse = 0.7;

	minirt->scene->light->pos = get_point3(-10, 10, -10);
	minirt->scene->camera->view.from = get_point3(0, 1.5, -5);
	minirt->scene->camera->view.to = get_point3(0, 1, 0);
	minirt->scene->camera->view.up = get_vec3(0, 1, 0);
	minirt->scene->camera->transform = get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv = get_inversed_matrix(minirt->scene->camera->transform);

}

void	load_special_scene(int number, t_minirt *minirt)
{
	if (number == 1)
		scene_1(minirt);
	else
		printf("no scene %d number yet...\n", number);
	return ;
}
