/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:58:05 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 15:02:04 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	vec3_debug_print(t_vec3 *vec3)
{
	if (!vec3)
		return (ft_printf("vec3_debug_print. Error, passed NULL pointer\n"), 1);
	ft_printf("Vec3: x=%d, y=%d, z=%d\n", vec3->x, vec3->y, vec3->z);
	return (0);
}
