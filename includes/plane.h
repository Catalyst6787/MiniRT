/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:29:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:29:58 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

typedef struct s_plane
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		color;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
}	t_plane;

#endif
