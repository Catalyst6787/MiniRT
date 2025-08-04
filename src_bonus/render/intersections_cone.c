#include "minirt.h"


bool	check_cone_cap(const t_ray *ray, double t, double y_cap)
{
	double	x;
	double	z;
	(void)y_cap;

	x = ray->origin.x + t * ray->dir.x;
	z = ray->origin.z + t * ray->dir.z;
	return ((x * x + z * z) <= 1);
	// return ((x * x + z * z) <= (y_cap * y_cap));
}

int	intersect_cone_caps(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	double	t;
	int		hit_added;

	hit_added = 0;
	if (!object->obj_data.cylinder.isclosed
		|| (ray->dir.y > -(EPSILON) && ray->dir.y < EPSILON))
		return (0);
	t = (object->obj_data.cylinder.min - ray->origin.y) / ray->dir.y;
	if (check_cone_cap(ray, t, object->obj_data.cylinder.min))
	{
		list->inters[list->count].t = t;
		list->inters[list->count].obj = object;
		list->count++;
		hit_added++;
	}
	t = (object->obj_data.cylinder.max - ray->origin.y) / ray->dir.y;
	if (check_cone_cap(ray, t, object->obj_data.cylinder.max))
	{
		list->inters[list->count].t = t;
		list->inters[list->count].obj = object;
		list->count++;
		hit_added++;
	}
	return (hit_added);
}

static int	store_cone_inter(t_cylinder_inter *d, const t_object *object,
				const t_ray *ray, t_inter_list *list)
{
	int	hits_added;

	hits_added = 0;
	if (d->t0 > d->t1)
		swap_doubles(&d->t0, &d->t1);
	d->y0 = ray->origin.y + d->t0 * ray->dir.y;
	if (object->obj_data.cylinder.min < d->y0
		&& d->y0 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = d->t0;
		list->inters[list->count].obj = object;
		list->count++;
		hits_added++;
	}
	d->y1 = ray->origin.y + d->t1 * ray->dir.y;
	if (object->obj_data.cylinder.min < d->y1
		&& d->y1 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = d->t1;
		list->inters[list->count].obj = object;
		list->count++;
		hits_added++;
	}
	return (hits_added);
}

int	get_cone_inter(const t_object *object,
	const t_ray *ray, t_inter_list *list)
{
	t_cylinder_inter	d;
	int					hits_added;

	hits_added = 0;
	if (list->count > list->capacity - 2)
		return (print_err(__FILE__, LINE,
				"get_cylinder_inter: no more space in list"), 1);
	d.a = pow(ray->dir.x, 2) - pow(ray->dir.y, 2) + pow(ray->dir.z, 2);
	d.b = 2 * ray->origin.x * ray->dir.x - 2 * ray->origin.y * ray->dir.y + 2 * ray->origin.z * ray->dir.z;
	d.c = pow(ray->origin.x, 2) - pow(ray->origin.y, 2) + pow(ray->origin.z, 2);
	if (d.a > -(EPSILON) && d.a < EPSILON)
	{
		if (d.b > -(EPSILON) && d.b < EPSILON)
			return (intersect_cone_caps(object, ray, list));
		list->inters[list->count].t = -(d.c) / (2 * d.b);
		list->inters[list->count].obj = object;
		list->count++;
		hits_added++;
		hits_added += intersect_cone_caps(object, ray, list);
		return (hits_added);
	}
	d.discriminant = (d.b * d.b) - (4 * d.a * d.c);
	if (d.discriminant < 0)
		return (intersect_cone_caps(object, ray, list));
	d.t0 = (-d.b - sqrtf(d.discriminant)) / (2.0 * d.a);
	d.t1 = (-d.b + sqrtf(d.discriminant)) / (2.0 * d.a);
	hits_added += store_cone_inter(&d, object, ray, list);
	hits_added += intersect_cone_caps(object, ray, list);
	return (hits_added);
}
