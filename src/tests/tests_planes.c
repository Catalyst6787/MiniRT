#include "minirt.h"

// int	get_plane_inter(const t_object *object, const t_ray ray, t_inter_list *list)
// {
	
// 	if (double_abs(ray.dir.y) < EPSILON)
// 		return (0);
// 	list->inters[list->count].t = (-(ray.origin.y) / ray.dir.y);
// 	list->inters[list->count].obj = object;
// 	list->count++;
// 	return (0);
// }


int			start_all_planes_tests(void)
{
	t_plane			*plane;
	t_ray			ray;
	t_object		plane_obj;
	t_vec3			normal;
	t_inter_list	list;
	(void)normal;

	plane = new_plane(get_point3(0, 0, 0), get_vec3(1, 0, 1), get_color(1, 1, 1));
	create_object_from_plane(&plane_obj, plane);
	normal = get_vec3(0, 1, 0);
	list.capacity = 1;
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.inters[0].t = 0;
	
	
	////////////	Test Ray Parallel
	
	list.count = 0;
	ray = get_ray(get_point3(0, 10, 0), get_vec3(0, 0, 1));
	get_plane_inter(&plane_obj, ray, &list);
	assert(!list.inters[0].t);

	////////////	Test Coplanar Ray

	list.count = 0;
	ray = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	get_plane_inter(&plane_obj, ray, &list);
	assert(!list.inters[0].t);

	////////////	Test plane intersected from above

	list.count = 0;
	ray = get_ray(get_point3(0, 1, 0), get_vec3(0, -1, 0));
	get_plane_inter(&plane_obj, ray, &list);
	assert(list.inters[0].t == 1);

	////////////	Test plane intersected from bellow

	list.count = 0;
	ray = get_ray(get_point3(0, -1, 0), get_vec3(0, 1, 0));
	get_plane_inter(&plane_obj, ray, &list);
	assert(list.inters[0].t == 1);

	free(plane);
	free(list.inters);

	return (0);
}

