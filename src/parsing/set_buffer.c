#include "minirt.h"

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


void	filter_buffer(t_minirt *minirt)
{
	int		len;
	char	*tmp;

	len = count_char_whithout_comments(minirt->scene->buffer);
	tmp = ft_strdup(minirt->scene->buffer);
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
	filter_buffer(minirt);
	if (close(fd) == -1)
		quit(minirt, CLOSING_FILE_ERR);
	if (!minirt->scene->buffer)
		quit(minirt, EMPTY_FILE);
}
