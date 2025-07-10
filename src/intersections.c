#include "minirt.h"

int	get_sphere_inter(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	if (!list)
		return (print_err(FILE, LINE, "get_sphere_inter: NULL pointer"), 1);
	oc = vec3_vec_substraction(ray->origin, get_point3(0, 0, 0));
	a = vec3_dot(ray->dir, ray->dir);
	b = 2.0 * vec3_dot(ray->dir, oc);
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

int	get_plane_inter(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	if (double_abs(ray->dir.y) < EPSILON)
		return (0);
	if (list->count > list->capacity - 1)
		return (print_err(FILE, LINE,
			"get_plane_inter: no more space in list"), 1);
	list->inters[list->count].t = (-(ray->origin.y) / ray->dir.y);
	list->inters[list->count].obj = object;
	list->count++;
	return (0);
}
bool	check_cap(const t_ray *ray, double t)
{
	double x;
	double z;
	

	x = ray->origin.x + t * ray->dir.x;
	z = ray->origin.z + t * ray->dir.z;
	return ((x * x + z * z) <= 1);
}

int	intersect_caps(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	double	t;
	int		hit_added;

	hit_added = 0;
	if (!object->obj_data.cylinder.isclosed || (ray->dir.y > -(EPSILON) &&  ray->dir.y < EPSILON))
		return (0);
	t = (object->obj_data.cylinder.min - ray->origin.y) / ray->dir.y;
	if (check_cap(ray, t))
	{
		list->inters[list->count].t = t;
		list->inters[list->count].obj = object;
		list->count++;
		hit_added++;
	}
	t = (object->obj_data.cylinder.max - ray->origin.y) / ray->dir.y;
	if (check_cap(ray, t))
	{
		list->inters[list->count].t = t;
		list->inters[list->count].obj = object;
		list->count++;
		hit_added++;
	}
	return (hit_added);
}


int	get_cylinder_inter(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	y0;
	double	y1;
	double	t0;
	double	t1;
	int		nb_inter;

	if (list->count > list->capacity - 2)
		return (print_err(FILE, LINE,
				"get_cylinder_inter: no more space in list"), 1);
	a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
	if ((a > -(EPSILON) && a < EPSILON))
		return (intersect_caps(object, ray, list));
	b = 2 * ray->origin.x * ray->dir.x + 2 * ray->origin.z * ray->dir.z;
	c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - 1;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (intersect_caps(object, ray, list));
	nb_inter = intersect_caps(object, ray, list);
	if (nb_inter == 2)
		return (0);
	t0 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0 * a);
	if (t0 > t1)
		swap_doubles(&t0, &t1);
	y0 = ray->origin.y + t0 * ray->dir.y;
	if (object->obj_data.cylinder.min < y0 && y0 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = t0;
		list->inters[list->count].obj = object;
		list->count++;
		nb_inter++;
	}
	if (nb_inter == 2)
		return (0);
	y1 = ray->origin.y + t1 * ray->dir.y;
	if (object->obj_data.cylinder.min < y1 && y1 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = t1;
		list->inters[list->count].obj = object;
		list->count++;
	}
	return (0);
}


int	get_intersection(t_object *object, t_ray *ray, t_inter_list *list)
{

	if (object->type == SPHERE)
		get_sphere_inter(object, ray, list);
	else if (object->type == PLANE)
		get_plane_inter(object, ray, list);
	else if (object->type == CYLINDER)
	{
		get_cylinder_inter(object, ray, list);
	}
	return (0);
}
