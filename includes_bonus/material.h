#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct s_material
{
	t_vec3	color;
	double	ambient;
	t_vec3	ambient_color;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

#endif
