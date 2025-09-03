/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:51:53 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 22:51:54 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_obj_type(t_object *obj, int *cursor, char *buffer)
{
	if (!buffer || !buffer[0] || !buffer[*cursor])
		return (1);
	if (!obj)
		return (1);
	else if (!ft_strncmp(buffer + *cursor, "sp", 2))
		obj->type = SPHERE;
	else if (!ft_strncmp(buffer + *cursor, "cy", 2))
		obj->type = CYLINDER;
	else if (!ft_strncmp(buffer + *cursor, "pl", 2))
		obj->type = PLANE;
	else if (!ft_strncmp(buffer + *cursor, "co", 2))
		obj->type = CONE;
	else
		return (1);
	(*cursor) += 2;
	return (0);
}

int	is_shearing(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != ' ' && s[i] != '\n')
		i++;
	while (s && s[i] && ft_isspace(s[i]))
		i++;
	if (ft_isdigit(s[i]))
		return (1);
	else
		return (0);
}

int	print_until(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	if (s && s[i])
		return (write(1, s, i));
	return (0);
}

int	check_direction_validity(t_vec3 dir)
{
	if (double_isequal(dir.x, 0)
		&& double_isequal(dir.y, 0)
		&& double_isequal(dir.z, 0))
		return (1);
	return (0);
}

int	check_scaling_validity(t_vec3 scaling)
{
	if (double_isequal(scaling.x, 0)
		|| double_isequal(scaling.y, 0)
		|| double_isequal(scaling.z, 0))
		return (1);
	return (0);
}
