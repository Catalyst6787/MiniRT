/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:30:02 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:30:03 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}			t_ray;

t_ray	get_ray(t_vec3 org, t_vec3 dir);
t_vec3	ray_at(double t, const t_ray *ray);
t_ray	ray_transform(t_ray r, t_matrix m);

#endif
