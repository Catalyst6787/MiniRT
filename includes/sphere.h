/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:51:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 17:15:29 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"

typedef struct s_sphere
{
	t_vec3		*pos;
	double		diameter;
	t_vec3		*color;
}	t_sphere;

int			hit_sphere(const t_sphere *sphere, const t_ray *ray);
t_sphere	*sphere_new_alloc(t_vec3 *pos, double diameter, t_vec3 *color);

#endif
