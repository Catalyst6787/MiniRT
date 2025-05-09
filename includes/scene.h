/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:56:19 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/09 17:00:32 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ambient
{
	double	brightness;
	t_color	*color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3			*pos;
	t_vec3			*dir;
	unsigned int	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3		*pos;
	double		brightness;
	t_color		*color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		*pos;
	double		diameter;
	t_color		*color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		*pos;
	t_vec3		*dir;
	t_color		*color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		*pos;
	t_vec3		*dir;
	double		diameter;
	double		height;
	t_color		*color;
}	t_cylinder;

typedef struct s_render
{
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	t_vec3	*camera_center;
	t_vec3	*viewport_u;
	t_vec3	*viewport_v;
	t_vec3	*pixel_delta_u;
	t_vec3	*pixel_delta_v;
	t_vec3	*viewport_upper_left;
	t_vec3	*pixel00_loc;
}	t_render;

typedef struct scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;
}	t_scene;

#endif
