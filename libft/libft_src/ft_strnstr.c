/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:28:14 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/04 12:37:08 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!n[i])
		return ((char *)h);
	while (h[i] && i < len)
	{
		while (h[i + j] && h[i + j] == n[j] && (i + j) < len)
			j++;
		if (!n[j])
			return ((char *)(h + i));
		else
			j = 0;
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strnstr("abcdefgabcdfeg", "abcdf", 4));
	return(0);
}
*/
