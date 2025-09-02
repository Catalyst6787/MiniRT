/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:57:24 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/02 11:38:44 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "vec3.h"
typedef struct s_ambient
{
	double		brightness;
	t_vec3		color;
}	t_ambient;

typedef struct s_view
{
	t_vec3		from;
	t_vec3		to;
	t_vec3		dir;
	t_vec3		up;
	double		yaw;
	double		pitch;
}				t_view;

typedef struct s_camera
{
	t_view			view;
	double			hsize;
	double			vsize;
	double			fov;
	double			pixel_size;
	double			half_width;
	double			half_height;
	t_matrix		transform;
	t_matrix		inv;
}	t_camera;

typedef struct s_light
{
	t_vec3		pos;
	double		brightness;
	t_vec3		color;
}	t_light;

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		**lights;
	// t_sphere	**spheres;
	// t_plane		**planes;
	// t_cylinder	**cylinders;
	// t_cone		**cones;
	t_object	*objects;
	char		*filename;
	char		*buffer;
	int			nb_amb;
	int			nb_cam;
	int			nb_light;
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
	int			nb_cone;
	int			nb_objects;
	t_object	*cone_debug;
}	t_scene;

#endif
