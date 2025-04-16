/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignedhex_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:03 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/15 17:57:47 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsignedhex_c(unsigned int n, unsigned int up)
{
	char	*base;
	char	*baseup;
	int		c;

	c = 0;
	base = "0123456789abcdef";
	baseup = "0123456789ABCDEF";
	if (n >= 16)
	{
		c += ft_putunsignedhex_c(n / 16, up);
		n = n % 16;
	}
	if (up)
		return (c + ft_putchar_c(baseup[n]));
	return (c + ft_putchar_c(base[n]));
}
