/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:15:35 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/04 11:28:00 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((unsigned char)p1[i] == (unsigned char)p2[i] && i < n - 1)
		i++;
	return ((unsigned char)p1[i] - (unsigned char)p2[i]);
}
/*
int memcmp(const void *s1, const void *s2, size_t n)
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_memcmp("test", "testss", 7));
	printf("%d\n", ft_memcmp("", "test", 4));
	return(0);
}
*/
