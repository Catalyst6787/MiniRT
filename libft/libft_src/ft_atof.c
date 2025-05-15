/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:49:15 by alvan-de          #+#    #+#             */
/*   Updated: 2025/05/15 12:31:17 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

double	ft_atof(char *str)
{
	double	right;
	double	result;
	int		i;
	int		len;
	char	*decimal_point;

	if (!str || !*str)
		return (0);
	result = (double)ft_atoi(str);
	decimal_point = ft_strchr(str, '.');
	if (!decimal_point)
		return (result);
	str = decimal_point + 1;
	if (!*str)
		return (result);
	right = (double)ft_atoi(str);
	len = ft_intlen((int)right);
	i = -1;
	while (++i < len)
		right *= 0.1;
	result += right;
	return (result);
}
