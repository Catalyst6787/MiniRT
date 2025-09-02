/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:26:31 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:40:19 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "minirt.h"

void	objects_alloc(t_minirt *minirt, t_scene *scene)
{
	scene->objects = malloc(sizeof(t_object) * (scene->nb_objects + 1));
	if (!scene->objects && scene->nb_objects)
		quit(minirt, MALLOC_ERR);
}

void	move_cursor(char *str, int *cursor, char c)
{
	int	i;

	i = *cursor;
	while (*str && *str != c && ++i)
		str++;
	while (*str && *str == c && ++i)
		str++;
	*cursor = i;
}

char	*trim_ato_ptr(char *ptr, int delim)
{
	int		i;
	char	*dest;

	i = 0;
	if (delim == ' ')
		while (ptr[i] && ptr[i] != delim && ptr[i] != '\t')
			i++;
	else
		while (ptr[i] && ptr[i] != delim)
			i++;
	dest = ft_substr(ptr, 0, i);
	return (dest);
}

double	ato_buffer(char *ptr, int *cursor, int delim)
{
	int		i;
	double	n;
	char	*n_str;

	i = *cursor;
	n_str = trim_ato_ptr(ptr, delim);
	n = ft_atof(n_str);
	move_cursor(ptr, &i, delim);
	if (n_str)
		free(n_str);
	*cursor = i;
	return (n);
}

void	set_scene_buffer(t_minirt *minirt)
{
	int		fd;

	fd = open(minirt->scene->filename, O_RDONLY);
	if (fd < 0)
		quit(minirt, FILE_OPEN_ERR);
	get_file_contents(fd, &minirt->scene->buffer);
	if (errno == 21)
		quit(minirt, DIRECTORY_ERR);
	if (!minirt->scene->buffer)
		quit(minirt, EMPTY_FILE);
	filter_buffer(minirt);
	if (close(fd) == -1)
		quit(minirt, CLOSING_FILE_ERR);
	if (!minirt->scene->buffer)
		quit(minirt, EMPTY_FILE);
}
