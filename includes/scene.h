#ifndef SCENE_H
# define SCENE_H

# include "matrice.h"
# include "sphere.h"
# include "cylinder.h"
# include "plane.h"
# include "vec3.h"

typedef struct s_ambient
{
	double		brightness;
	t_vec3		color;
}	t_ambient;

typedef struct s_view
{
	t_vec3		from;
	t_vec3		to;
	t_vec3		up;
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
	t_light		*light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;
	t_object	*objects;
	char		*filename;
	char		*buffer;
	int			nb_amb;
	int			nb_cam;
	int			nb_light;
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
	int			nb_objects;
}	t_scene;



#endif
