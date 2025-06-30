#include "minirt.h"

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

int	get_plane_inter(const t_object *object, const t_ray ray, t_inter_list *list)
{
	if (double_abs(ray.dir.y) < EPSILON)
		return (0);
	if (list->count > list->capacity - 1)
		return (print_err(FILE, LINE,
				"get_plane_inter: no more space in list"), 1);
	list->inters[list->count].t = (-(ray.origin.y) / ray.dir.y);
	list->inters[list->count].obj = object;
	list->count++;
	return (0);
}
