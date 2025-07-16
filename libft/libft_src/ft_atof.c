/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:49:15 by alvan-de          #+#    #+#             */
/*   Updated: 2025/07/16 17:16:39 by alvan-de         ###   ########.fr       */
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
	int		count_zeros;

	i = 0;
	while (str[i] == '0')
		i++;
	count_zeros = i;
	right = (double)ft_atoi(str);
	len = ft_intlen((int)right);
	i = 0;
	while (i < count_zeros)
	{
		right *= 0.1;
		i++;
	}
	i = 0;
	while (i < len)
	{
		right *= 0.1;
		i++;
	}
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
