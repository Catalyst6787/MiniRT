/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:57:09 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:57:10 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_type;

typedef struct s_cylinder_limits
{
	double	min;
	double	max;
	bool	isclosed;
}				t_cylinder_limits;

typedef union u_original_obj
{
	t_vec3				plane_normal;
	t_cylinder_limits	cylinder;
}				t_original_obj;

typedef struct s_object
{
	t_type			type;
	t_matrix		translation;
	t_vec3			dir;
	t_matrix		rotation;
	t_matrix		shearing;
	t_matrix		scaling;
	t_matrix		transform;
	t_matrix		inv;
	t_material		material;
	t_original_obj	obj_data;
	int				id;
}				t_object;

#endif
