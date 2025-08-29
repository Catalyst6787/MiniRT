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
