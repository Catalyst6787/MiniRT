#include "minirt.h"

int	get_sphere_inter(const t_object *object, const t_ray ray, t_inter_list *list)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	if (!list)
		return (print_err(FILE, LINE, "get_sphere_inter: NULL pointer"), 1);
	oc = vec3_vec_substraction(ray.origin, get_point3(0, 0, 0));
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(ray.dir, oc);
	c = vec3_dot(oc, oc) - 1;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0);
	if (list->count > list->capacity - 2)
		return (print_err(FILE, LINE,
				"get_sphere_inter: no more space in list"), 1);
	list->inters[list->count].t = ((-b - sqrtf(discriminant)) / (2.0 * a));
	list->inters[list->count].obj = object;
	list->count++;
	list->inters[list->count].t = ((-b + sqrtf(discriminant)) / (2.0 * a));
	list->inters[list->count].obj = object;
	list->count++;
	return (0);
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

int	get_intersection(t_object *object, t_ray ray, t_inter_list *list)
{
	if (object->type == SPHERE)
		get_sphere_inter(object, ray, list);
	if (object->type == PLANE)
		get_plane_inter(object, ray, list);

	/*       ADD NEXT :       */

	// else if (object->type == CYLINDER)
	// 	get_cylinder_inter(object, ray, list);
	return (0);
}
