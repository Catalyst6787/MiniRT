/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:47:22 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/07 22:02:15 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*tmp_ptr;
	unsigned char	c;

	c = 0;
	tmp_ptr = (unsigned char *) b;
	while (n > 0)
	{
		*(tmp_ptr++) = (unsigned char) c;
		n--;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char b[24] = "testest0A* @?<>{}[]test";
	printf("%s\n", b);
	ft_bzero(b, 23);
	printf("%s\n", b);
	return (0);
}
*/
