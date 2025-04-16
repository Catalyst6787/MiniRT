/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:19:16 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/04 14:40:01 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
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
		nstr[i] = src[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac < 2)
		return(0);
	printf("%s\n", ft_strdup(av[1]));
	return (0);
}
*/
