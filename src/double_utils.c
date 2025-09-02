/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:13:14 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:23:25 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

int	double_isequal(double a, double b)
{
	if (double_abs(a - b) < EPSILON)
		return (1);
	return (0);
}
