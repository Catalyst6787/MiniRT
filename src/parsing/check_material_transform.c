/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_material_transform.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:10:19 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 23:10:20 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_color_validity(t_vec3 color)
{
	if (color.r > 255 || color.r < 0)
		return (1);
	if (color.g > 255 || color.g < 0)
		return (1);
	if (color.b > 255 || color.b < 0)
		return (1);
	return (0);
}

int	check_transformation_data(t_vec3 transformations[4])
{
	if (check_direction_validity(transformations[direction]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_DIRECTION), direction);
	if (check_scaling_validity(transformations[scaling]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_SCALE), scaling);
	if (check_color_validity(transformations[color]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_COLOR), color);
	return (0);
}

int	check_material_data(t_material material)
{
	if (material.ambient > 1 || material.ambient < 0)
		return (1);
	if (check_color_validity(material.ambient_color))
		return (1);
	if (material.diffuse > 1 || material.diffuse < 0)
		return (1);
	if (material.specular > 1 || material.specular < 0)
		return (1);
	if (material.shininess > 500 || material.shininess < 1)
		return (1);
	if (material.reflective > 1 || material.reflective < 0)
		return (1);
	return (0);
}
