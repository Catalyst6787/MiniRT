#ifndef OBJECT_H
# define OBJECT_H

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_object
{
	t_type		type;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
	t_vec3		plane_normal;
}	t_object;

#endif
