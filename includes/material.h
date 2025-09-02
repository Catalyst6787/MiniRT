/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:29:32 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:30:55 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct s_material
{
	t_vec3	color;
	double	ambient;
	t_vec3	ambient_color;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

#endif
