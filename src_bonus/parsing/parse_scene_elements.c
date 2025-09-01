/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:30 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:58:10 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <stdio.h>

static int parse_buffer(t_minirt *minirt,
						int *cursor,
						t_parsing_helper *ph)
{
	while (minirt->scene->buffer[*cursor] && (ft_isspace(minirt->scene->buffer[*cursor]) || minirt->scene->buffer[*cursor] == '\n'))
		(*cursor)++;
	while (minirt->scene->buffer[*cursor] && minirt->scene->buffer[*cursor] == '#')
	{
		while (minirt->scene->buffer[*cursor] && minirt->scene->buffer[*cursor] != '\n')
			(*cursor)++;
		while (minirt->scene->buffer[*cursor] && (ft_isspace(minirt->scene->buffer[*cursor]) || minirt->scene->buffer[*cursor] == '\n'))
			(*cursor)++;
	}
	if (!minirt->scene->buffer[*cursor])
		return(quit(minirt, "parse_buffer reached unexpected EOF\n"), 1);
	if (minirt->scene->buffer[*cursor] == 'A' && !ph->a)
		return (parse_ambiant_light(minirt, minirt->scene, cursor), ph->a = true, 0);
	else if (minirt->scene->buffer[*cursor] == 'C' && !ph->c)
		return (parse_camera(minirt, minirt->scene, cursor), ph->c = true, 0);
	else if (minirt->scene->buffer[*cursor] == 'L' && ph->l < minirt->scene->nb_light)
		return(parse_light(minirt, minirt->scene, minirt->scene->lights[ph->l++], cursor), 0);
	else if (ph->o < minirt->scene->nb_objects)
		return(parse_object(minirt, &minirt->scene->objects[ph->o++], cursor), 0);
	else if (minirt->scene->buffer[*cursor] != '\n')
		return(printf("\n%s", minirt->scene->buffer + *cursor), quit(minirt, "parse_buffer: unrecognized expression"), 1);
	return(0);
}

void	parse_scene_elements(t_minirt *minirt, t_scene *scene)
{
	int					cursor;
	t_parsing_helper	ph;

	cursor = 0;
	ft_memset(&ph, 0, sizeof(t_parsing_helper));
	while (scene->buffer[cursor] && (!ph.a || !ph.c || ph.l < minirt->scene->nb_light || ph.o < minirt->scene->nb_objects))
	{
		parse_buffer(minirt, &cursor, &ph);
	}
}
