/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_scaling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:55 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:51:55 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// if scaling by -1,-1,-1 you get a reflection.
t_matrix	get_scaling_matrix(t_vec3 v)
{
	t_matrix	m;

	m = get_matrix(4, 4, 1);
	m.matrix[0][0] = v.x;
	m.matrix[1][1] = v.y;
	m.matrix[2][2] = v.z;
	return (m);
}
