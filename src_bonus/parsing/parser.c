/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:36 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/02 12:15:22 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	test_light_sum(t_scene *scene)
{
	int		i;
	double	tot;

	i = 0;
	tot = scene->ambient->brightness;
	while (i < scene->nb_light)
	{
		tot += scene->lights[i]->brightness;
		i++;
	}
	if (tot > 1.0)
		printf("%sWarning, sum of lights > 1!%s\n", RED, CRESET);
}

void	fill_obj_id(t_scene *scene)
{
	int	i;
	int	sp;
	int	pl;
	int	cy;
	int	co;

	i = 0;
	sp = 0;
	pl = 0;
	cy = 0;
	co = 0;
	while (i < scene->nb_objects)
	{
		if (scene->objects[i].type == SPHERE)
			scene->objects[i].id = sp++;
		else if (scene->objects[i].type == PLANE)
			scene->objects[i].id = pl++;
		else if (scene->objects[i].type == CYLINDER)
			scene->objects[i].id = cy++;
		else if (scene->objects[i].type == CONE)
			scene->objects[i].id = co++;
		i++;
	}
}

void	parse_scene(t_minirt *minirt)
{
	minirt->scene->buffer = NULL;
	if (!ft_strncmp(minirt->scene->filename,
			"scenes/random_generation.rt", 21))
		generate_random_scene(minirt);
	check_file_name(minirt);
	set_scene_buffer(minirt);
	check_file_not_empty(minirt);
	check_characters_validity(minirt);
	check_object_format(minirt, minirt->scene->buffer);
	check_each_lines(minirt, minirt->scene->buffer);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_scene_elements(minirt, minirt->scene);
	set_camera_transformation(minirt->scene);
	check_data_validity(minirt, minirt->scene);
	fill_obj_id(minirt->scene);
	fill_intersection_table(minirt, minirt->render);
	set_selected_object_data(minirt, minirt->scene);
	test_light_sum(minirt->scene);
	if (minirt->scene->nb_cone)
		minirt->scene->cone_debug = &minirt->scene->objects[0];
}
