/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_orientations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:47 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:51:48 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

void	dir_to_yaw_pitch(t_view *view)
{
	view->pitch = asinf(view->dir.y);
	view->yaw = atan2(view->dir.z, view->dir.x);
}

t_vec3	yaw_pitch_to_dir(double yaw, double pitch)
{
	t_vec3	dir;

	dir.x = cosf(pitch) * cosf(yaw);
	dir.y = sinf(pitch);
	dir.z = cosf(pitch) * sinf(yaw);
	dir.w = 0;
	return (vec3_normalise(dir));
}

// from view.dir
t_matrix	get_orientation_matrix(t_view view)
{
	t_vec3		left;
	t_vec3		true_up;
	t_matrix	orientation;

	view.dir = yaw_pitch_to_dir(view.yaw, view.pitch);
	left = vec3_cross(view.dir, view.up);
	true_up = vec3_cross(left, view.dir);
	orientation = get_matrix(4, 4, 1);
	orientation.matrix[0][0] = left.x;
	orientation.matrix[0][1] = left.y;
	orientation.matrix[0][2] = left.z;
	orientation.matrix[1][0] = true_up.x;
	orientation.matrix[1][1] = true_up.y;
	orientation.matrix[1][2] = true_up.z;
	orientation.matrix[2][0] = -(view.dir.x);
	orientation.matrix[2][1] = -(view.dir.y);
	orientation.matrix[2][2] = -(view.dir.z);
	orientation = multiply_matrix(orientation,
			get_translation_matrix(get_vec3(-(view.from.x),
					-(view.from.y),
					-(view.from.z))));
	return (orientation);
}
