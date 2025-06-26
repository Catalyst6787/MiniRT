#include "minirt.h"

int	get_plane_inter(const t_object *plane, const t_ray ray, t_inter_list *list)
{
	(void) plane;
	(void) ray;
	(void) list;
	// if (!list)
	// 	return (print_err(FILE, LINE, "get_plane_inter: NULL pointer"), 1);

	// if (list->count > list->capacity - 1)
	// 	return (print_err(FILE, LINE,
	// 			"get_plane_inter: no more space in list"), 1);
	// if (fabs(ray.dir.y) < EPSILON)
	// 	return (0);
	// // list->inters[list->count].t = ((-1) * ray.origin.y) / ray.dir.y;
	// t_vec3	v1 = vec3_vec_substraction(plane->pos, ray.origin);
	// list->inters[list->count].t = vec3_dot(v1, plane->dir) / vec3_dot(ray.dir, plane->dir);
	// if (list->inters[list->count].t < 0)
	// 	return (0);
	// list->inters[list->count].obj = plane;
	// list->count++;
	return (0);
}


