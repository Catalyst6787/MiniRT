#include "minirt.h"


t_cone	*new_cone(t_vec3 pos, t_vec3 dir, double diameter, double height, t_vec3 color)
{
	t_cone	*cone;

	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (perror("new_cone. Error\n"), NULL);
	cone->pos = pos;
	cone->dir = dir;
	cone->color = color;
	cone->material = get_material();
	cone->material.color = color;
	cone->diameter = diameter;
	cone->radius = diameter / 2;
	cone->height = height;
	cone->transform = get_matrix(4, 4, 1);
	cone->inv = get_matrix(4, 4, 1);
	return (cone);
}

int			start_all_cones_tests(void)
{
	t_cone			*cone;
	t_object		cone_obj;
	t_ray			ray;
	t_inter_list	list;
	(void) ray;

	cone = new_cone(get_point3(0, 0, 0), get_vec3(0, 1, 0), 1, 100, get_color(1, 1, 1));
	create_object_from_cone(&cone_obj, cone, 0);
	cone_obj.obj_data.cylinder.isclosed = 0;
	list.capacity = 4;
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	list.inters[0].t = 0;

	//////////	Test Intersections

		//////	2 inter

	list.count = 0;
	ray = get_ray(get_point3(0, 0, -5), vec3_normalise(get_vec3(0, 0, 1)));
	get_cone_inter(&cone_obj, &ray, &list);
	assert(list.inters[0].t == 5);
	assert(list.inters[1].t == 5);


	list.count = 0;
	ray = get_ray(get_point3(0, 0, -5), vec3_normalise(get_vec3(1, 1, 1)));
	get_cone_inter(&cone_obj, &ray, &list);
	assert(list.inters[0].t == 8.6602540378443855);
	assert(list.inters[1].t == 8.6602540378443855);

	list.count = 0;
	ray = get_ray(get_point3(1, 1, -5), vec3_normalise(get_vec3(-0.5, -1, 1)));
	get_cone_inter(&cone_obj, &ray, &list);
	assert(list.inters[0].t == 4.5500564575195277);
	assert(list.inters[1].t == 49.449943542480469);

		////////	1 inter

	list.count = 0;
	ray = get_ray(get_point3(0, 0, -1), vec3_normalise(get_vec3(0, 1, 1)));
	get_cone_inter(&cone_obj, &ray, &list);

	assert(list.inters[0].t == 0.35355339059327379);
	assert(list.count == 1);

	//////////	Test End Cap

	cone_obj.obj_data.cylinder.isclosed = 1;
	cone_obj.obj_data.cylinder.max = 0.5;
	cone_obj.obj_data.cylinder.min = -0.5;


	list.count = 0;
	ray = get_ray(get_point3(0, 0, -5), vec3_normalise(get_vec3(0, 1, 0)));
	get_cone_inter(&cone_obj, &ray, &list);
	assert(list.count == 0);

	list.count = 0;
	ray = get_ray(get_point3(0, 0, -0.25), vec3_normalise(get_vec3(0, 1, 1)));
	get_cone_inter(&cone_obj, &ray, &list);
	print_inter_list(&list);
	assert(list.count == 2);

	list.count = 0;
	ray = get_ray(get_point3(0, 0, -0.25), vec3_normalise(get_vec3(0, 1, 0)));
	get_cone_inter(&cone_obj, &ray, &list);
	assert(list.count == 4);


	free(list.inters);
	free(cone);

	return (0);
}
