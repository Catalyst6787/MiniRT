/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:52:50 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:53:02 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"
#include "minirt.h"
#include <stdlib.h>

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

void	filter_buffer(t_minirt *minirt)
{
	int		len;
	char	*tmp;
	char	*no_dup_sp;

	len = count_char_whithout_comments(minirt->scene->buffer);
	tmp = str_dup_no_tab(minirt->scene->buffer);
	no_dup_sp = str_dedup_sp(tmp);
	free(tmp);
	tmp = no_dup_sp;
	if (!no_dup_sp)
		quit(minirt, MALLOC_ERR);
	if (!tmp)
		quit(minirt, MALLOC_ERR);
	free(minirt->scene->buffer);
	minirt->scene->buffer = malloc(sizeof(char) * (len + 1));
	if (!minirt->scene->buffer)
	{
		free(tmp);
		quit(minirt, MALLOC_ERR);
	}
	strcpy_filter_comments(minirt->scene->buffer, tmp);
	free(tmp);
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
	filter_buffer(minirt);
	if (close(fd) == -1)
		quit(minirt, CLOSING_FILE_ERR);
	if (!minirt->scene->buffer)
		quit(minirt, EMPTY_FILE);
}
