#ifndef PLANE_H
# define PLANE_H

# include "minirt.h"

typedef struct s_plane
{
	t_vec3		*pos;
	t_vec3		*dir;
	t_vec3		*color;
}	t_plane;


#endif