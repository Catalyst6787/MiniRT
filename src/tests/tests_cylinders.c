#include "minirt.h"

// int	get_cylinder_inter(const t_object *object, const t_ray ray, t_inter_list *list)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;
// 	double	y0;
// 	double	y1;
// 	double	t0;
// 	double	t1;

// 	a = pow(ray.dir.x, 2) + pow(ray.dir.z, 2);
// 	if (a > -(EPSILON) && a < EPSILON) // if a is approximately zero
// 		return (0);
// 	b = 2 * ray.origin.x * ray.dir.x + 2 * ray.origin.z * ray.dir.z;
// 	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
// 	discriminant = (b * b) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (0);
// 	if (list->count > list->capacity - 2)
// 		return (print_err(FILE, LINE,
// 				"get_cylinder_inter: no more space in list"), 1);
// 	t0 = (-b - sqrtf(discriminant)) / (2.0 * a);
// 	t1 = (-b + sqrtf(discriminant)) / (2.0 * a);
// 	if (t0 > t1)
// 		swap_doubles(&t0, &t1);
// 	y0 = ray.origin.y + t0 * ray.dir.y;
// 	if (object->obj_data.cylinder.min < y0 && y0 < object->obj_data.cylinder.max)
// 	{
// 		list->inters[list->count].t = t0;
// 		list->inters[list->count].obj = object;
// 		list->count++;
// 	}
// 	y1 = ray.origin.y + t1 * ray.dir.y;
// 	if (object->obj_data.cylinder.min < y1 && y1 < object->obj_data.cylinder.max)
// 	{
// 		list->inters[list->count].t = t1;
// 		list->inters[list->count].obj = object;
// 		list->count++;
// 	}
// 	return (1);
// }

// t_vec3	get_cylinder_normal_at(const t_object *cy, const t_vec3 world_point)
// {
// 	(void) cy;
// 	return (get_vec3(world_point.x, 0, world_point.z));
// }

int	start_all_cylinders_tests(void)
{
	t_cylinder		*cy;
	t_object		cy_object;
	t_ray			r;
	t_inter_list	list;

	cy = new_cylinder(get_point3(0, 0, 0), get_vec3(0, 1, 0), 2, 100, get_color(1, 1, 1));
	create_object_from_cylinder(&cy_object, cy);
	cy_object.obj_data.cylinder.min = INT_MIN;
	cy_object.obj_data.cylinder.max = INT_MAX;

	list.capacity = 2;
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.inters[0].t = 0;

	////////////	Tests no intersection

	list.count = 0;
	r = get_ray(get_point3(1, 0, 0), get_vec3(0, 1, 0));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.inters[0].t);

	list.count = 0;
	r = get_ray(get_point3(0, 0, 0), get_vec3(0, 1, 0));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.inters[0].t);

	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(1, 1, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.inters[0].t);

	////////////	Tests intersections

	list.count = 0;
	r = get_ray(get_point3(1, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(list.inters[0].t == 5);
	assert(list.inters[1].t == 5);

	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);

	assert(list.inters[0].t == 4);
	assert(list.inters[1].t == 6);

	list.count = 0;
	r = get_ray(get_point3(0.5, 0, -5), get_vec3(0.1, 1, 1));
	get_cylinder_inter(&cy_object, r, &list);
	// printf("%.5f\n", list.inters[0].t);
	// printf("%.5f\n", list.inters[1].t);
	// assert(list.inters[0].t == 6.80798);
	// assert(list.inters[1].t == 7.08872);

	////////////	Tests truncated Cylinders

	cy_object.obj_data.cylinder.min = 1;
	cy_object.obj_data.cylinder.max = 2;

	/* 1 */
	list.count = 0;
	r = get_ray(get_point3(0, 1.5, 0), get_vec3(0.1, 1, 0));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.count);
	/* 2 */
	list.count = 0;
	r = get_ray(get_point3(0, 3, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.count);
	/* 3 */
	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.count);
	/* 4 */
	list.count = 0;
	r = get_ray(get_point3(0, 2, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.count);
	/* 5 */
	list.count = 0;
	r = get_ray(get_point3(0, 1, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(!list.count);
	/* 6 */
	list.count = 0;
	r = get_ray(get_point3(0, 1.5, -2), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, r, &list);
	assert(list.count);



	free(cy);
	free(list.inters);
	return (0);
}
