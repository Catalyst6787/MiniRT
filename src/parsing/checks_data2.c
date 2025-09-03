/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_data2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:55:28 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 15:55:29 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_data_validity_extra(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->nb_plane)
		if (!is_ok_dir(scene->planes[i]->dir)
			|| !is_ok_color(scene->planes[i]->color))
			quit(minirt, WRONG_PLANE_DATA);
	i = -1;
	while (++i < scene->nb_cylinder)
		if (!is_ok_dir(scene->cylinders[i]->dir)
			|| !is_ok_color(scene->cylinders[i]->color)
			|| !is_ok_scale(scene->cylinders[i]->diameter)
			|| !is_ok_scale(scene->cylinders[i]->height))
			quit(minirt, WRONG_CYL_DATA);
}
