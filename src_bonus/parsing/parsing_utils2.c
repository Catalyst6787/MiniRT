/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 22:47:43 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// return a vector (w = 0), set w to 1 for a point
t_vec3	ato_vec3(char *s, int *cursor, t_minirt *minirt)
{
	t_vec3	v;

	if (!s || !s[0])
		quit(minirt, "ato_vec encountered empty str");
	while (ft_isspace(s[*cursor]))
		cursor++;
	v.x = ato_buffer(s + *cursor, cursor, ',');
	v.y = ato_buffer(s + *cursor, cursor, ',');
	v.z = ato_buffer(s + *cursor, cursor, ' ');
	v.w = 0;
	return (v);
}
