/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:49:15 by alvan-de          #+#    #+#             */
/*   Updated: 2025/07/11 16:34:40 by lfaure           ###   ########.fr       */
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

double	get_right(char *str)
{
	double	right;
	int		len;
	int		i;

	right = (double)ft_atoi(str);
	len = ft_intlen((int)right);
	i = -1;
	while (++i < len)
		right *= 0.1;
	return (right);
}

double	ft_atof(char *str)
{
	double	result;
	int		i;
	char	*decimal_point;
	int		sign;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	if (str[i] == '-' && str[i + 1] == '0')
		sign = -1;
	result = (double)ft_atoi(str);
	decimal_point = ft_strchr(str, '.');
	if (!decimal_point)
		return (result);
	str = decimal_point + 1;
	if (!*str)
		return (result);
	if (result >= 0)
		result += get_right(str);
	else
		result -= get_right(str);
	return (result * sign);
}
