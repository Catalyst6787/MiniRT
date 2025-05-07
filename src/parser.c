/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:11:25 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/07 14:04:49 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// O_RDWR fails on dir
// we then drop useless permissions

int	check_file(char *file_path, int *fd)
{
	if (!file_path || !file_path[0])
		return (ft_printf("Error\nFile path cannot be empty.\n"), 1);
	if (ft_strncmp(file_path + ft_strlen(file_path) - 3, ".rt", 3))
		return (ft_printf("Error\nFile must be in .rt format\n"), 1);
	if (ft_strlen(file_path) <= 3)
		return (ft_printf("Error\nFile name cannot be empty\n"));
	*fd = open(file_path, O_RDWR | __O_NOFOLLOW);
	if (*fd == -1)
		return (perror("Error\nFile failed to open"), 1);
	close(*fd);
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		return (perror("Error\nFile failed to open"), 1);
	return (0);
}

int	get_file_contents(int fd, char **file_contents)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	tmp = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		if (*file_contents)
			tmp = *file_contents;
		*file_contents = ft_strjoin(*file_contents, buf);
		if (tmp)
			free(tmp);
		tmp = NULL;
		free(buf);
		buf = get_next_line(fd);
	}
	if (!*file_contents)
		return (1);
	return (0);
}

int	parse(char *file_path, t_scene *scene)
{
	int		fd;
	char	*file_contents;
	char	**scene_arr;
	int		i;

	fd = 0;
	file_contents = NULL;
	i = 0;
	if (check_file(file_path, &fd))
		return (1);
	if (get_file_contents(fd, &file_contents))
		return (close(fd),
			ft_printf("Error\nFile: <%s> is empty\n", file_path), 1);
	scene_arr = ft_split(file_contents, '\n');
	ft_printf("file contents:\n%s\n", file_contents);
	while(scene_arr && scene_arr[i])
	{
		ft_printf("row%d: %s\n", i, scene_arr[i]);
		i++;
	}
	i = 0;
	while (scene_arr && scene_arr[i])
	{
		free(scene_arr[i]);
		i++;
	}
	free(scene_arr);
	close(fd);
	free(file_contents);
	return (0);
	(void)scene;
}
