/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:53:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/15 12:29:38 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	size_t	totlen;
	size_t	i;
	size_t	j;
	char	*nstr;

	i = 0;
	j = 0;
	totlen = ft_strlen(s1) + ft_strlen(s2);
	nstr = malloc(sizeof(char) * (totlen + 1));
	if (!nstr)
		return (NULL);
	while (s1 && s1[i])
		nstr[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		nstr[j++] = s2[i++];
	nstr[j] = '\0';
	return (nstr);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*nstr;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (nstr = malloc(1 * sizeof(char)), nstr[0] = '\0', nstr);
// 	if (len > ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	if (start > ft_strlen(s))
// 		return (NULL);
// 	nstr = malloc(len + 1 * sizeof(char));
// 	if (!nstr)
// 		return (NULL);
// 	while (s[i] && i < len)
// 	{
// 		nstr[i] = s[start + i];
// 		i++;
// 	}
// 	nstr[i] = '\0';
// 	return (nstr);
// }

int	checkline(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1])
			return (2);
		else if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
