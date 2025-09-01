/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_orientations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:24:27 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:24:28 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	get_orientation_matrix(t_view view)
{
	t_vec3		forward;
	t_vec3		left;
	t_vec3		true_up;
	t_matrix	orientation;

	forward = vec3_normalise(vec3_vec_substraction(view.to, view.from));
	left = vec3_cross(forward, vec3_normalise(view.up));
	true_up = vec3_cross(left, forward);
	orientation = get_matrix(4, 4, 1);
	orientation.matrix[0][0] = left.x;
	orientation.matrix[0][1] = left.y;
	orientation.matrix[0][2] = left.z;
	orientation.matrix[1][0] = true_up.x;
	orientation.matrix[1][1] = true_up.y;
	orientation.matrix[1][2] = true_up.z;
	orientation.matrix[2][0] = -(forward.x);
	orientation.matrix[2][1] = -(forward.y);
	orientation.matrix[2][2] = -(forward.z);
	orientation = multiply_matrix(orientation,
			get_translation_matrix(get_vec3(-(view.from.x),
					-(view.from.y),
					-(view.from.z))));
	return (orientation);
}
