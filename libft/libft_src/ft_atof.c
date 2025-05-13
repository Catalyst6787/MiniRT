/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:49:15 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/13 13:01:40 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	right;
	double	result;
	int		i;
	int		len;

	result = ft_atoi(str);
	while (*str != '.')
		str++;
	str++;
	right = ft_atoi(str);
	len = ft_intlen((int)right);
	i = -1;
	while (++i < len)
		right *= 0.1;
	result += right;
	return (result);
}
