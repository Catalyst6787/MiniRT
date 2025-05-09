/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_complex_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:58:35 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/09 15:02:14 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// good for quick length comparison, less precise but faster than
// vec3_exact_lenght
double	vec3_length_squared(t_vec3 *vec3)
{
	assert(vec3);
	return (vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
}

double	vec3_exact_length(t_vec3 *vec3)
{
	assert(vec3);
	return (sqrt(vec3_length_squared(vec3)));
}

void	vec3_normalise_inplace(t_vec3 *vec3)
{
	double	length;

	assert(length != 0);
	assert(vec3);
	length = vec3_exact_length(vec3);
	vec3->x /= length;
	vec3->y /= length;
	vec3->z /= length;
}

// commutative
double	vec3_dot(t_vec3 *vec3_u, t_vec3 *vec3_v)
{
	assert(vec3_u);
	assert(vec3_v);
	return ((vec3_u->x * vec3_v->x)
		+ (vec3_u->y * vec3_v->y)
		+ (vec3_u->z * vec3_v->z));
}
