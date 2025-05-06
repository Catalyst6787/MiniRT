/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:11:25 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 19:32:50 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// O_RDWR fails on dir
// we then drop useless permissions
int	parse(char *file_path, t_scene *scene)
{
	char	*total_file;
	char	*line;
	char	*tmp;
	int		fd;

	total_file = "";
	line = "";
	tmp = NULL;
	fd = 0;
	if (!file_path || !file_path[0])
		return (ft_printf("Error\nFile path cannot be empty.\n"), 1);
	if (ft_strncmp(file_path + ft_strlen(file_path) - 3, ".rt", 3))
		return (ft_printf("Error\nFile must be in .rt format\n"), 1);
	if (ft_strlen(file_path) <= 3)
		return (ft_printf("Error\nFile name cannot be empty\n"));

	fd = open(file_path, O_RDWR | __O_NOFOLLOW);
	if (fd == -1)
		return (perror("Error\nFile failed to open"), 1);
	close(fd);
	fd = open(file_path, O_RDONLY);

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(total_file))
			tmp = total_file;
		total_file = ft_strjoin(total_file, line);
		free(line);
		if (tmp)
			free(tmp);
		line = get_next_line(fd);
	}
	ft_printf(total_file);
	close(fd);
	free(total_file);
	return (0);
	(void)scene;
}
