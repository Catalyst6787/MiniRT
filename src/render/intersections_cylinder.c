#include "minirt.h"

bool	check_cap(const t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->dir.x;
	z = ray->origin.z + t * ray->dir.z;
	return ((x * x + z * z) <= 1);
}

int	intersect_caps(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	double	t;
	int		hit_added;

	hit_added = 0;
	if (!object->obj_data.cylinder.isclosed
		|| (ray->dir.y > -(EPSILON) && ray->dir.y < EPSILON))
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

static int	store_cylinder_inter(t_cylinder_inter *d, const t_object *object,
				const t_ray *ray, t_inter_list *list)
{
	if (d->t0 > d->t1)
		swap_doubles(&d->t0, &d->t1);
	d->y0 = ray->origin.y + d->t0 * ray->dir.y;
	if (object->obj_data.cylinder.min < d->y0
		&& d->y0 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = d->t0;
		list->inters[list->count].obj = object;
		list->count++;
		d->nb_inter++;
	}
	if (d->nb_inter == 2)
		return (0);
	d->y1 = ray->origin.y + d->t1 * ray->dir.y;
	if (object->obj_data.cylinder.min < d->y1
		&& d->y1 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = d->t1;
		list->inters[list->count].obj = object;
		list->count++;
	}
	return (0);
}

int	get_cylinder_inter(const t_object *object,
	const t_ray *ray, t_inter_list *list)
{
	t_cylinder_inter	d;

	if (list->count > list->capacity - 2)
		return (print_err(FILE, LINE,
				"get_cylinder_inter: no more space in list"), 1);
	d.a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
	if ((d.a > -(EPSILON) && d.a < EPSILON))
		return (intersect_caps(object, ray, list));
	d.b = 2 * ray->origin.x * ray->dir.x + 2 * ray->origin.z * ray->dir.z;
	d.c = pow(ray->origin.x, 2) + pow(ray->origin.z, 2) - 1;
	d.discriminant = (d.b * d.b) - (4 * d.a * d.c);
	if (d.discriminant < 0)
		return (intersect_caps(object, ray, list));
	d.nb_inter = intersect_caps(object, ray, list);
	if (d.nb_inter == 2)
		return (0);
	d.t0 = (-d.b - sqrtf(d.discriminant)) / (2.0 * d.a);
	d.t1 = (-d.b + sqrtf(d.discriminant)) / (2.0 * d.a);
	return (store_cylinder_inter(&d, object, ray, list));
}
