/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:26:22 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:26:23 by lfaure           ###   ########.fr       */
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
		else if (scene->buffer[i] == 'c' && scene->buffer[++i] == 'y')
			scene->nb_cylinder++;
	}
	scene->nb_objects = scene->nb_sphere + scene->nb_plane
		+ scene->nb_cylinder;
}

void	parse_scene(t_minirt *minirt)
{
	minirt->scene->buffer = NULL;
	check_file_name(minirt);
	set_scene_buffer(minirt);
	check_file_not_empty(minirt);
	check_characters_validity(minirt);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_scene_elements(minirt, minirt->scene);
	set_objects_transformation(minirt->scene);
	set_objects_material(minirt->scene);
	check_data_validity(minirt, minirt->scene);
	create_object_list(minirt->scene);
	fill_intersection_table(minirt, minirt->render);
	set_selected_object_str(minirt, minirt->scene);
	free(minirt->scene->buffer);
	minirt->scene->buffer = NULL;
}
