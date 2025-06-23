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
	t_vec3		pos;
	t_vec3		dir;
	double		diameter;
	double		radius;
	t_vec3		color;
	double		height;
}	t_object;

#endif
