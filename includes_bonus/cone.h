#ifndef CONE_H
# define CONE_H

typedef struct s_cone
{
	t_vec3		pos;
	t_vec3		dir;
	double		diameter;
	double		radius;
	double		height;
	t_vec3		color;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
}	t_cone;

#endif
