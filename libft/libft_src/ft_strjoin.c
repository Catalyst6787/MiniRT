/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:45:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/07 13:37:24 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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

/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strjoin("Welcome to ", "42"));
	return (0);
}
*/
