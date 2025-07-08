#include "minirt.h"


typedef struct s_cone
{
	t_vec3		pos;
	t_vec3		dir;
	double		diameter;
	double		radius;
	double		height;
	t_vec3		color;
	t_matrix	transform;
	t_matrix	inv;
	t_material	material;
}				t_cone;



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

void	create_object_from_cone(t_object *object, t_cone *cone)
{
	object->type = CONE;
	object->material = cone->material;
	object->transform = cone->transform;
	object->inv = cone->inv;
	object->obj_data.cylinder.max = cone->height / 2;
	object->obj_data.cylinder.min = -(cone->height) / 2;
	// object->obj_data.cone.max = 0.5;
	// object->obj_data.cone.min = -0.5;
	// object->obj_data.cone.max = cone->height / 2;
	// object->obj_data.cone.min = -(cone->height / 2);


}

int	get_cone_inter(const t_object *object, const t_ray *ray, t_inter_list *list)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	y0;
	double	y1;
	double	t0;
	double	t1;

	a = pow(ray->dir.x, 2) - pow(ray->dir.y, 2) + pow(ray->dir.z, 2);
	b = 2 * ray->origin.x * ray->dir.x - 2 * ray->origin.y * ray->dir.y + 2 * ray->origin.z * ray->dir.z;
	c = pow(ray->origin.x, 2) - pow(ray->origin.y, 2) + pow(ray->origin.z, 2);
	if (a > -(EPSILON) && a < EPSILON && b) // if a is approximately zero
	{
		list->inters[list->count].t = -(c) / (2 * b);
		list->inters[list->count].obj = object;
		list->count++;
		return (printf("a = 0\n"), 1);
	}
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0);
	if (list->count > list->capacity - 2)
		return (print_err(FILE, LINE,
				"get_cylinder_inter: no more space in list"), 1);
	t0 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0 * a);
	if (t0 > t1)
		swap_doubles(&t0, &t1);
	y0 = ray->origin.y + t0 * ray->dir.y;
	if (object->obj_data.cylinder.min < y0 && y0 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = t0;
		list->inters[list->count].obj = object;
		list->count++;
	}
	y1 = ray->origin.y + t1 * ray->dir.y;
	if (object->obj_data.cylinder.min < y1 && y1 < object->obj_data.cylinder.max)
	{
		list->inters[list->count].t = t1;
		list->inters[list->count].obj = object;
		list->count++;
	}
	return (1);
}


int			start_all_cones_tests(void)
{
	t_cone			*cone;
	t_object		cone_obj;
	t_ray			ray;
	t_inter_list	list;
	(void) ray;

	cone = new_cone(get_point3(0, 0, 0), get_vec3(0, 1, 0), 2, 100, get_color(1, 1, 1));
	create_object_from_cone(&cone_obj, cone);
	list.capacity = 2;
	list.inters = malloc(sizeof(t_inter) * list.capacity);
	// list.inters[0].t = 0;

	////////////	Test Intersections

	// list.count = 0;
	// ray = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
	// get_cone_inter(&cone_obj, &ray, &list);
	// assert(list.inters[0].t == 5);
	// assert(list.inters[1].t == 5);


	// list.count = 0;
	// ray = get_ray(get_point3(0, 0, -5), get_vec3(1, 1, 1));
	// get_cone_inter(&cone_obj, &ray, &list);
	// printf("Inter count : %d\n", list.count);
	// printf("t0 : %.5f\n", list.inters[0].t);
	// printf("t1 : %.5f\n", list.inters[1].t);
	// assert(list.inters[0].t == 8.66025);
	// assert(list.inters[1].t == 8.66025);

	// list.count = 0;
	// ray = get_ray(get_point3(1, 1, -5), get_vec3(-0.5, -1, 1));
	// get_cone_inter(&cone_obj, &ray, &list);
	// assert(list.inters[0].t == 4.55006);
	// assert(list.inters[1].t == 49.44994);




	free(list.inters);
	free(cone);

	return (0);
}
