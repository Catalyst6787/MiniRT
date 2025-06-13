#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "sphere.h"
# include "cylinder.h"
# include "plane.h"

typedef struct s_ambient
{
	double		brightness;
	t_vec3		*color;
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
	t_vec3		*color;
}	t_light;


typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;
	char		*buffer;
	int			nb_amb;
	int			nb_cam;
	int			nb_light;
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
}	t_scene;

#endif
