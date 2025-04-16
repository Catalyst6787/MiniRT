/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:02:31 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/04 12:26:33 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *) b;
	while (len > 0)
	{
		*(tmp_ptr++) = (unsigned char) c;
		len--;
	}
	return (b);
}

/*
#include <stdio.h>
int	main(void)
{
	char b[24] = "testest0A* @?<>{}[]test";
	//void *p = &b;
	printf("%s\n", b);
	ft_memset(b, 'A', 23);
	printf("%s\n", b);
	return (0);
}
*/
