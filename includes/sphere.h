/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:30:21 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:30:22 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

typedef struct s_sphere
{
	t_vec3		pos;
	t_vec3		color;
	double		diameter;
	double		radius;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
}	t_sphere;

#endif
