/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:11:25 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/07 16:24:19 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	choose_parser(char *line, t_scene *scene)
{
	if (line[0] == '#')
		return (0);
	else if (!ft_strncmp(line, "A ", 2))
		return (parse_ambiant(line, scene));
	else if (!ft_strncmp(line, "C ", 2))
		return (parse_camera(line, scene));
	else if (!ft_strncmp(line, "L ", 2))
		return (parse_light(line, scene));
	else if (!ft_strncmp(line, "sp ", 3))
		return (parse_sphere(line, scene));
	else if (!ft_strncmp(line, "pl ", 3))
		return (parse_plane(line, scene));
	else if (!ft_strncmp(line, "cy ", 3))
		return (parse_cylinder(line, scene));
	else
		return (ft_printf("field: <%s> is malformed. usage: <id> <...>\n",
				line), 1);
}

static int	parse_fields(char **scene_arr, t_scene *scene)
{
	int	i;

	i = 0;
	while (scene_arr[i])
	{
		if (choose_parser(scene_arr[i], scene))
			return (1);
		i++;
	}
	return (0);
}

int	parse(char *file_path, t_scene *scene)
{
	int		fd;
	int		err;
	char	*file_contents;
	char	**scene_arr;

	fd = 0;
	err = 0;
	file_contents = NULL;
	scene_arr = NULL;
	if (check_file(file_path, &fd))
		return (1);
	if (get_file_contents(fd, &file_contents))
		return (close(fd),
			ft_printf("Error\nFile: <%s> is empty\n", file_path), 1);
	scene_arr = ft_split(file_contents, '\n');
	if (!scene_arr || !scene_arr[0])
		return (close(fd), free(scene_arr), free(file_contents),
			ft_printf("Error\nFile: <%s> is empty\n", file_path), 1);
	err = parse_fields(scene_arr, scene);
	free_tab(scene_arr);
	free_and_null((void **)&scene_arr);
	close(fd);
	free(file_contents);
	return (err);
}
