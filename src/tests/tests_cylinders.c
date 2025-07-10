#include "minirt.h"


int	start_all_cylinders_tests(void)
{
	t_cylinder		*cy;
	t_object		cy_object;
	t_ray			r;
	t_inter_list	list;

	cy = new_cylinder(get_point3(0, 0, 0), get_vec3(0, 1, 0), 2, 100, get_color(1, 1, 1));
	create_object_from_cylinder(&cy_object, cy, 0);
	cy_object.obj_data.cylinder.min = INT_MIN;
	cy_object.obj_data.cylinder.max = INT_MAX;
	cy_object.obj_data.cylinder.isclosed = 0;

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
	r = get_ray(get_point3(0.5, 0, -5), vec3_normalise(get_vec3(0.1, 1, 1)));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.inters[0].t == 6.807981925946395);
	assert(list.inters[1].t == 7.0887234304597859);

	// ////////////	Tests truncated Cylinders

	cy_object.obj_data.cylinder.min = 1;
	cy_object.obj_data.cylinder.max = 2;

	/* 1 */
	list.count = 0;
	r = get_ray(get_point3(0, 1.5, 0), vec3_normalise(get_vec3(0.1, 1, 0)));
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

	////////////	Caped Cylinders

	cy_object.obj_data.cylinder.isclosed = 1;

	/* 1 */
	list.count = 0;
	r = get_ray(get_point3(0, 3, 0), vec3_normalise(get_vec3(0, -1, 0)));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.count == 2);
	/* 2 */
	list.count = 0;
	r = get_ray(get_point3(0, 3, -2), vec3_normalise(get_vec3(0, -1, 2)));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.count == 2);
	/* 3 */
	list.count = 0;
	r = get_ray(get_point3(0, 4, -2), vec3_normalise(get_vec3(0, -1, 1)));
	get_cylinder_inter(&cy_object, &r, &list);
	print_inter_list(&list);
	assert(list.count == 2);
	/* 4 */
	list.count = 0;
	r = get_ray(get_point3(0, 0, -2), vec3_normalise(get_vec3(0, 1, 2)));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.count == 2);
	/* 4 */
	list.count = 0;
	r = get_ray(get_point3(0, -1, -2), vec3_normalise(get_vec3(0, 1, 1)));
	get_cylinder_inter(&cy_object, &r, &list);
	assert(list.count == 2);

	////////////	Cylinders normals

	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0,1,0)),get_vec3(0, -1, 0)));
	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0.5,1,0)),get_vec3(0, -1, 0)));
	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0,1,0.5)),get_vec3(0, -1, 0)));
	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0,2,0)),get_vec3(0, 1, 0)));
	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0.5,2,0)),get_vec3(0, 1, 0)));
	assert(vec3_isequal(get_cylinder_normal_at(&cy_object, get_point3(0,2,0.5)),get_vec3(0, 1, 0)));



	free(cy);
	free(list.inters);
	return (0);
}
