/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:56:19 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 18:08:20 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_position {
	double	x;
	double	y;
	double	z;
}	t_position;

typedef struct s_color {
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray {
	t_vec	*orientation;
	t_color	*color;
	double	brightness;
}	t_ray;

typedef struct s_ambient
{
	double	brightness;
	t_color	*color;
}	t_ambient;


typedef struct s_camera {
	t_position		*pos;
	t_vec			*orientation;
	unsigned int	fov;
}	t_camera;

typedef struct s_light {
	t_position	*pos;
	double		brightness;
	t_color		*color;
}	t_light;

typedef struct s_sphere
{
	t_position	*pos;
	double		diameter;
	t_color		*color;
}	t_sphere;

typedef struct s_plane
{
	t_position	*pos;
	t_vec		*orientation;
	t_color		*color;
}	t_plane;

typedef struct s_cylinder
{
	t_position	*pos;
	t_vec		*orientation;
	double		diameter;
	double		height;
	t_color		*color;
}	t_cylinder;

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
