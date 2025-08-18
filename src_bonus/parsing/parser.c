#include "minirt.h"

void	count_elements(t_scene *scene)
{
	int	i;

	i = -1;
	while (scene->buffer[++i])
	{
		if (scene->buffer[i] == 'A')
			scene->nb_amb++;
		else if (scene->buffer[i] == 'C')
			scene->nb_cam++;
		else if (scene->buffer[i] == 'L')
			scene->nb_light++;
		else if (scene->buffer[i] == 's' && scene->buffer[++i] == 'p')
			scene->nb_sphere++;
		else if (scene->buffer[i] == 'p' && scene->buffer[++i] == 'l')
			scene->nb_plane++;
		else if (scene->buffer[i] == 'c')
		{
			if (scene->buffer[++i] == 'y')
				scene->nb_cylinder++;
			else if (scene->buffer[i] == 'o')
				scene->nb_cone++;
		}
	}
	scene->nb_objects = scene->nb_sphere + scene->nb_plane
		+ scene->nb_cylinder + scene->nb_cone;
}

void	parse_scene(t_minirt *minirt)
{
	PRINT_DEBUG("\n%s\n\n", minirt->scene->filename);
	minirt->scene->buffer = NULL;
	if (!ft_strncmp(minirt->scene->filename, "assets/scenes/random_generation.rt", 21))
		generate_random_scene();
	check_file_name(minirt);
	set_scene_buffer(minirt);
	check_file_not_empty(minirt);
	check_characters_validity(minirt);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_scene_elements(minirt, minirt->scene);
	set_camera_transformation(minirt->scene);
	// set_objects_material(minirt->scene);
	check_data_validity(minirt, minirt->scene);
	// create_object_array(minirt->scene);
	// print_scene_ok_message(minirt->scene->filename);
	debug_print_scene_data(minirt);
	fill_intersection_table(minirt, minirt->render);
	set_selected_object_str(minirt, minirt->scene);
	debug_print_objects_pointers(minirt->scene);
	free(minirt->scene->buffer);
	minirt->scene->buffer = NULL;
}
