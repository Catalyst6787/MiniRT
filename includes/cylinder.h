#ifndef CYLINDER_H
# define CYLINDER_H

# include "minirt.h"

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		dir;
	double		diameter;
	double		height;
	t_vec3		color;
}	t_cylinder;


#endif

