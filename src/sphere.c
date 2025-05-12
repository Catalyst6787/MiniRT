/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:25:31 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 17:15:45 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_sphere(const t_sphere *sphere, const t_ray *ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	ft_memset(&oc, 0, sizeof(t_vec3));
	vec3_copy(&oc, sphere->pos);
	vec3_substract_inplace(&oc, ray->origin);
	a = vec3_dot(ray->dir, ray->dir);
	b = -2.0 * vec3_dot(ray->dir, &oc);
	c = vec3_dot(&oc, &oc) - (sphere->diameter * sphere->diameter);
	discriminant = (b * b) - (4 * a * c);
	return (discriminant >= 0);
}

t_sphere	*sphere_new_alloc(t_vec3 *pos, double diameter, t_vec3 *color)
{
	t_sphere	*sphere;

	if (!pos || !color)
		return (ft_printf("sphere_new_alloc. Error, passed NULL ptr.\n"), NULL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("sphere_new_alloc. Error\n"), NULL);
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}
