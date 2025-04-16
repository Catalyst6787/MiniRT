/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:56:57 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/15 17:57:44 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_c(char *s)
{
	int	i;

	if (s == NULL)
		return (ft_putstr_c("(null)"));
	i = 0;
	while (s[i])
		ft_putchar_c(s[i++]);
	return (i);
}
