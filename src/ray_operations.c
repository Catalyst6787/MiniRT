/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:25:14 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/09 14:27:10 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	*ray_position_at(t_ray *ray, const double t)
{
	t_vec3	*result;

	result = vec3_default_alloc();
	result->x = ray->origin->x + (t * ray->dir->x);
	result->y = ray->origin->y + (t * ray->dir->x);
	result->z = ray->origin->z + (t * ray->dir->x);
	return (result);
}
