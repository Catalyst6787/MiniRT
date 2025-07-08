#include "minirt.h"

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
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.inters[0].t);

	list.count = 0;
	r = get_ray(get_point3(0, 0, 0), get_vec3(0, 1, 0));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.inters[0].t);

	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(1, 1, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.inters[0].t);

	////////////	Tests intersections

	list.count = 0;
	r = get_ray(get_point3(1, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.inters[0].t == 5);
	assert(list.inters[1].t == 5);

	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);

	assert(list.inters[0].t == 4);
	assert(list.inters[1].t == 6);

	list.count = 0;
	r = get_ray(get_point3(0.5, 0, -5), get_vec3(0.1, 1, 1));
	get_cylinder_inter(&cy_object, &r, &list);
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
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.count);
	/* 2 */
	list.count = 0;
	r = get_ray(get_point3(0, 3, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.count);
	/* 3 */
	list.count = 0;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.count);
	/* 4 */
	list.count = 0;
	r = get_ray(get_point3(0, 2, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.count);
	/* 5 */
	list.count = 0;
	r = get_ray(get_point3(0, 1, -5), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(!list.count);
	/* 6 */
	list.count = 0;
	r = get_ray(get_point3(0, 1.5, -2), get_vec3(0, 0, 1));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.count);



	free(cy);
	free(list.inters);
	return (0);
}
