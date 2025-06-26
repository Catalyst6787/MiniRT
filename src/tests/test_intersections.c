#include "minirt.h"

int	test_ray_intersect_sphere(void)
{
	t_ray			r;
	t_object		s;
	t_inter			inter[10]; // can be malloc'ed aswell
	t_inter_list	lst;
	int				i;

	// inter = malloc(sizeof(t_inter) * 10);

	ft_memset(&inter, 0, sizeof(t_inter) * 10);
	lst.count = 0;
	lst.capacity = 10;
	lst.inters = inter;
	// debug_print_inter_list(lst);
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	// s.color = get_color(1, 0, 0);
	// s.pos = get_point3(0, 0, 0);
	// s.diameter = 2;
	// a ray interescts a sphere at two points
	get_sphere_inter(&s, r, &lst);
	assert(lst.count == 2);
	assert(lst.inters[0].t == 4.0);
	assert(lst.inters[1].t == 6.0);
	// a ray intersects a sphere at a tangent
	r = get_ray(get_point3(0, 1, -5), get_vec3(0, 0, 1));
	get_sphere_inter(&s, r, &lst);
	assert(lst.count == 4);
	assert(lst.inters[2].t == 5);
	assert(lst.inters[3].t == 5);
	assert(lst.inters[2].t == lst.inters[3].t);
	// a ray misses a sphere
	r = get_ray(get_point3(0, 2, -5), get_vec3(0, 0, 1));
	get_sphere_inter(&s, r, &lst);
	assert(lst.count == 4);
	assert(lst.inters[4].t == 0 && lst.inters[5].t == 0); // not yet set
	// a ray originates inside a sphere
	r = get_ray(get_point3(0, 0, 0), get_vec3(0, 0, 1));
	get_sphere_inter(&s, r, &lst);
	assert(lst.count == 6);
	assert(lst.inters[4].t == -1.0);
	assert(lst.inters[5].t == 1.0);
	// a sphere is behing a ray
	r = get_ray(get_point3(0, 0, 5), get_vec3(0, 0, 1));
	get_sphere_inter(&s, r, &lst);
	assert(lst.count == 8);
	assert(lst.inters[6].t == -6.0);
	assert(lst.inters[7].t == -4.0);

	// test sort intersections
	// debug_print_inter_list(lst);
	sort_inter(&lst);
	i = 0;
	while (i < lst.count - 1)
	{
		assert(lst.inters[i].t <= lst.inters[i + 1].t);
		i++;
	}


	return (0);
}

int	start_all_intersection_tests(void)
{
	test_ray_intersect_sphere();
	printf("test_ray_intersect_sphere passed\n");
	return (0);
}
