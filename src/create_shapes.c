#include "minirt.h"

t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("new_sphere. Error\n"), NULL);
	sphere->pos = pos;
	sphere->pos.w = 1;
	sphere->diameter = diameter;
	sphere->radius = diameter / 2;
	sphere->color = color;
	sphere->material = get_material();
	sphere->material.color = color;
	sphere->transform = get_matrix(4, 4, 1);
	sphere->inv = get_matrix(4, 4, 1);
	return (sphere);
}

t_plane	*new_plane(t_vec3 pos, t_vec3 dir, t_vec3 color)
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (perror("new_plane. Error\n"), NULL);
	plane->pos = pos;
	plane->dir = dir;
	plane->color = color;
	plane->material = get_material();
	plane->material.color = color;
	plane->transform = get_matrix(4, 4, 1);
	plane->inv = get_matrix(4, 4, 1);
	return (plane);
}

t_cylinder	*new_cylinder(t_vec3 pos, t_vec3 dir, double diameter, double height, t_vec3 color)
{
	t_cylinder	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (perror("new_cylinder. Error\n"), NULL);
	cylinder->pos = pos;
	cylinder->dir = dir;
	cylinder->color = color;
	cylinder->material = get_material();
	cylinder->material.color = color;
	cylinder->diameter = diameter;
	cylinder->radius = diameter / 2;
	cylinder->height = height;
	cylinder->transform = get_matrix(4, 4, 1);
	cylinder->inv = get_matrix(4, 4, 1);
	return (cylinder);
}

