#include "minirt.h"

int	basic_ray_test(void)
{
	t_ray r;

	r = get_ray(get_point3(2, 3, 4), get_vec3(1, 0, 0));
	assert(vec3_isequal(ray_at(0, r), get_point3(2, 3, 4)));
	assert(vec3_isequal(ray_at(1, r), get_point3(3, 3, 4)));
	assert(vec3_isequal(ray_at(-1, r), get_point3(1, 3, 4)));
	assert(vec3_isequal(ray_at(2.5, r), get_point3(4.5, 3, 4)));
	return (0);
}

int	test_ray_intersect_sphere()
{
	t_ray			r;
	t_sphere		s;
	t_vec3			c;
	t_vec3			pos;
	t_inter			inter[10]; // can be malloc'ed aswell
	t_inter_list	lst;

	// inter = malloc(sizeof(t_inter) * 10);
	ft_memset(&inter, 0, sizeof(t_inter) * 10);
	lst.count = 0;
	lst.capacity = 10;
	lst.inters = inter;
	r = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	c = get_color(1, 0, 0);
	pos = get_point3(0, 0, 0);
	s.color = &c;
	s.pos = &pos;
	s.diameter = 2;
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
	return (0);
}

int	start_all_ray_tests(void)
{
	basic_ray_test();
	printf("basic_ray_test passed\n");
	test_ray_intersect_sphere();
	printf("test_ray_intersect_sphere passed\n");
	return (0);
}
