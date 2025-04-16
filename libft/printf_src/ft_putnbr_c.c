/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:56:53 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/15 17:57:42 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_c(int n)
{
	int	c;

	c = 0;
	if (n == INT_MIN)
	{
		ft_putstr_c("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		c += ft_putchar_c('-');
		n = -n;
	}
	if (n >= 10)
	{
		c += ft_putnbr_c(n / 10);
		n = n % 10;
	}
	return (c + ft_putchar_c((n) + '0'));
}
