/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlonghex_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:56:49 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/16 12:47:22 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlonghex_c(unsigned long n, unsigned int up, int a)
{
	char	*base;
	char	*baseup;
	int		c;

	c = 0;
	if (a)
		c += ft_putstr_c("0x");
	base = "0123456789abcdef";
	baseup = "0123456789ABCDEF";
	if (n >= 16)
	{
		c += ft_putlonghex_c(n / 16, up, 0);
		n = n % 16;
	}
	if (up)
		return (c + ft_putchar_c(baseup[n]));
	return (c + ft_putchar_c(base[n]));
}
