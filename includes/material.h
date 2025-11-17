/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:56:48 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:57:46 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "vec3.h"

typedef struct s_material
{
	t_vec3	color;
	double	ambient;
	t_vec3	ambient_color;
	double	diffuse;
	double	specular;
	double	shininess;
	double	reflective;
}	t_material;

#endif
