/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:27 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:58:11 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bits/types/__FILE.h"
#include "errors.h"
#include "libft.h"
#include "material.h"
#include "matrice.h"
#include "minirt.h"
#include "object.h"
#include "scene.h"
#include "vec3.h"
#include <stdio.h>

int	count_comas(char *buffer, int i)
{
	int	count;

	count = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	count_spaces_in_line(char *buffer, int i)
{
	int	count;

	count = 0;
	while (buffer [i] && !ft_isspace(buffer[i]))
		i++;
	while (buffer [i] && ft_isspace(buffer[i]))
		i++;
	while (buffer[i] && buffer[i] != '\n')
	{
		while (buffer[i] && !ft_isspace(buffer[i]))
			i++;
		if (buffer[i] == '\t' || buffer[i] == ' ')
		{
			while (buffer[i] && ft_isspace(buffer[i]))
				i++;
			count++;
		}
		if (!buffer[i] || buffer[i] == '\n')
			break ;
		i++;
	}
	if (buffer[i] == '\n' && ft_isspace(buffer[i - 1]))
		count--;
	return (count);
}

int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 2
		|| count_spaces_in_line(scene->buffer, i) != 1)
	{
		printf("d = %d\n", count_spaces_in_line(scene->buffer, i));
		quit(minirt, WRONG_AMB_DATA);
	}
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->ambient->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->ambient->color.w = 0;
	*cursor = i;
	return (1);
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4
		|| count_spaces_in_line(scene->buffer, i) != 2)
		quit(minirt, WRONG_CAM_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i])
		&& scene->buffer[i] != '-')
		i++;
	scene->camera->view.from.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.from.w = 1;
	scene->camera->view.dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.dir.w = 0;
	check_direction_vector(minirt, &scene->camera->view.dir);
	scene->camera->view.to = get_vec3(0, 0, 0);
	scene->camera->view.up = get_vec3(0, 1, 0);
	scene->camera->hsize = WIN_W;
	scene->camera->vsize = WIN_H;
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n')
		* M_PI / 180;
	return (*cursor = i, 1);
}

int	parse_light(t_minirt *minirt, t_scene *scene, t_light *light, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4
		|| count_spaces_in_line(scene->buffer, i) != 2)
		quit(minirt, WRONG_LIGHT_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i])
		&& scene->buffer[i] != '-')
		i++;
	light->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	light->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	light->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	light->pos.w = 1;
	light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	light->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	light->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	light->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	light->color.w = 0;
	*cursor = i;
	return (1);
}
