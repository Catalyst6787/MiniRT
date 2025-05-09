/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:02:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/09 15:12:27 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray
{
	t_vec3	*origin;
	t_vec3	*dir;
	// t_color	*color;
	// double	brightness;
}	t_ray;

t_ray	*ray_default_alloc(void);
t_ray	*ray_new_alloc(t_vec3 *origin, t_vec3 *dir);
int		ray_init(t_ray *ray, t_vec3 *origin, t_vec3 *dir);
t_ray	*ray_dup_alloc(t_ray *to_dup);
t_vec3	*ray_position_at(t_ray *ray, const double t);


#endif
