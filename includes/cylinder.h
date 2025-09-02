/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:29:07 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:29:08 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		dir;
	double		diameter;
	double		radius;
	double		height;
	t_vec3		color;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
}	t_cylinder;

#endif
