/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:13:02 by lfaure            #+#    #+#             */
/*   Updated: 2024/11/06 22:58:51 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// c is the choice of action to perform
char	*get_stat(char *s1, int c, int fd)
{
	static char	*stat[4096];

	if (c == 0)
	{
		if (stat[fd])
			free(stat[fd]);
		stat[fd] = NULL;
	}
	else if (c == 1)
	{
		if (stat[fd])
			free(stat[fd]);
		stat[fd] = s1;
	}
	else if (c == 2)
		return (stat[fd]);
	else if (c == 3)
		stat[fd] = NULL;
	return (stat[fd]);
}

char	*until_nl(char *line, int freeline)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n' && freeline)
		{
			tmp = ft_substr(line, 0, i + 1);
			return (free(line), line = NULL, tmp);
		}
		else if (line[i] == '\n')
			return (ft_substr(line, 0, i + 1));
		i++;
	}
	return (NULL);
}

char	*after_nl(char *line)
{
	unsigned int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1])
			return (ft_substr(line, i + 1, ft_strlen(line)));
		else if (line[i] == '\n')
			return (NULL);
		i++;
	}
	return (NULL);
}

char	*get_next_line2(int chars_read, char *tmp, int fd)
{
	if (chars_read == -1)
		return (free(tmp), tmp = NULL, get_stat(NULL, 0, fd), NULL);
	if (get_stat(NULL, 2, fd))
	{
		tmp = ft_strjoin(get_stat(NULL, 2, fd), "");
		get_stat(NULL, 0, fd);
	}
	return (get_stat(NULL, 3, fd), tmp);
}

char	*get_next_line(int fd)
{
	int		chars_read;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	tmp = NULL;
	if (get_stat(NULL, 2, fd) && checkline(get_stat(NULL, 2, fd)))
	{
		tmp = until_nl(get_stat(NULL, 2, fd), 0);
		get_stat(after_nl(get_stat(NULL, 2, fd)), 1, fd);
		return (tmp);
	}
	chars_read = read(fd, buf, BUFFER_SIZE);
	while (chars_read > 0)
	{
		buf[chars_read] = '\0';
		tmp = ft_strjoin(get_stat(NULL, 2, fd), buf);
		if (checkline(tmp) == 2)
			return (get_stat(after_nl(tmp), 1, fd), until_nl(tmp, 1));
		else if (checkline(tmp) == 1)
			return (get_stat(NULL, 0, fd), tmp);
		get_stat(tmp, 1, fd);
		chars_read = read(fd, buf, BUFFER_SIZE);
	}
	return (get_next_line2(chars_read, tmp, fd));
}

/*
int main(void)
{
	int fd;
	fd = open("./files/variable_nls.txt", O_RDONLY);
	
	char* returnvalue;

	int i = 0;
	char	*tmp;
	while(i != 10)
	{
		returnvalue = get_next_line(fd);
		printf("%s", returnvalue);
		free(returnvalue);
		returnvalue = NULL;
		if (i == 11)
			{
				tmp = ft_strdup("");
				free(tmp);
				tmp = NULL;
			}
		i++;
	}

	printf("\n");


}

*/