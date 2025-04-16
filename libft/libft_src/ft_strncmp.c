/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:28:14 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/04 10:45:29 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_strncmp("test", "testss", 7));
	printf("%d\n", ft_strncmp("", "test", 4));
	return(0);
}
*/
