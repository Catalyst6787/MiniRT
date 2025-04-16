/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:07:36 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/03 16:04:12 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (src < dst)
		while (len--)
			d[len] = s[len];
	else
		while (len--)
			*d++ = *s++;
	return (dst);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(void)
{
	char *str = "abcde";
	char *dst = str + 2;
	char *src = str;
	char **psrc = &src;
	char **pdst = &dst;

	char *cstr = "abcde";
	char *cdst = cstr + 2;
	char *csrc = str;
	char **cpsrc = &csrc;
	char **cpdst = &cdst;
	
	ft_memmove(psrc, pdst, 3);
	memmove(cpsrc, cpdst, 3);

	while(*str)
	{
		if (*str++ != *cstr++)
			printf("ft_memmove != memmove");
	}
	printf("ft_memmove behaving as expected :D\n");

	printf("%s\n", src);
	printf("%s\n", dst);
	return (0);
}
*/
