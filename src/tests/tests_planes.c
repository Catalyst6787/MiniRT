#include "minirt.h"

int			start_all_planes_tests(void)
{
	t_plane			*plane;
	t_ray			ray;
	t_object		plane_obj;
	t_inter_list	list;

	plane = new_plane(get_point3(0, 0, 0), get_vec3(1, 0, 1), get_color(1, 1, 1));
	create_object_from_plane(&plane_obj, plane);
	list.capacity = 1;
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.inters[0].t = 0;
	
	
	////////////	Test Ray Parallel
	
	list.count = 0;
	ray = get_ray(get_point3(0, 10, 0), get_vec3(0, 0, 1));
	get_plane_inter(&plane_obj, &ray, &list);
	assert(!list.inters[0].t);

	////////////	Test Coplanar Ray

	list.count = 0;
	ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	get_plane_inter(&plane_obj, &ray, &list);
	assert(!list.inters[0].t);

	////////////	Test plane intersected from above

	list.count = 0;
	ray = get_ray(get_point3(0, 1, 0), get_vec3(0, -1, 0));
	get_plane_inter(&plane_obj, &ray, &list);
	assert(list.inters[0].t == 1);

	////////////	Test plane intersected from bellow

	list.count = 0;
	ray = get_ray(get_point3(0, -1, 0), get_vec3(0, 1, 0));
	get_plane_inter(&plane_obj, &ray, &list);
	assert(list.inters[0].t == 1);

	free(plane);
	free(list.inters);

	return (0);
}

