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

int	count_char_whithout_comments(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '#')
			while (buffer[i] && buffer[i] != '\n')
				i++;
		i++;
		count++;
	}
	return (count);
}

void	strcpy_filter_comments(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
	{
		if (s2[i] == '#')
			while (s2[i] && s2[i] != '\n')
				i++;
		s1[j] = s2[i];
		i++;
		j++;
	}
	s1[j] = '\0';
}

char	*str_dup_no_tab(char *src)
{
	int		len;
	char	*nstr;
	int		i;

	i = 0;
	len = ft_strlen(src);
	nstr = (char *)malloc(sizeof(*src) * (len + 1));
	if (!nstr)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '\t')
			nstr[i] = ' ';
		else
			nstr[i] = src[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	*str_dedup_sp(char *src)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return(NULL);
	ft_memset(res, 0, sizeof(char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		if (src[i] == ' ' && (src[i + 1] == ' ' || src[i + 1] == '\n'))
			i++;
		else
		{
			res[j++] = src[i++];
		}
	}
	return(res);
	for (int i = 0; res[i]; i++)
		if (res[i] == res[i + 1] && res[i] == ' ')
			printf("\nYOU FUCKING DUMBASS\n");
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
