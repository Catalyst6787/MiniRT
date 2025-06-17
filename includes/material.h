#include "minirt.h"

typedef struct s_material
{
	t_vec3	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

t_material	get_material(void);
t_material	get_default_material(t_vec3 color);
