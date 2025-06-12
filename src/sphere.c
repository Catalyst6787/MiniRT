
#include "minirt.h"
#include "vec3.h"

t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (perror("new_sphere. Error\n"), NULL);
	sphere->pos.x = pos.x;
	sphere->pos.y = pos.y;
	sphere->pos.z = pos.z;
	sphere->pos.w = 1;
	sphere->diameter = diameter;
	sphere->radius = diameter / 2;
	sphere->color.x = color.x;
	sphere->color.y = color.y;
	sphere->color.z = color.z;
	return (sphere);
}


int	get_sphere_inter(const t_sphere *sphere, const t_ray ray, t_inter_list *list)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	if (!list)
		return (print_err(FILE, LINE, "get_sphere_inter: NULL pointer"), 1);
	oc = vec3_vec_substraction(ray.origin, sphere->pos);
	a = vec3_dot(&ray.dir, &ray.dir);
	b = 2.0 * vec3_dot(&ray.dir, &oc);
	c = vec3_dot(&oc, &oc) - 1;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0);
	if (list->count >= list->capacity - 2)
		return (print_err(FILE, LINE,
				"get_sphere_inter: no more space in list"), 1);
	list->inters[list->count].t = ((-b - sqrt(discriminant)) / (2.0 * a));
	list->inters[list->count].obj = sphere;
	list->count++;
	list->inters[list->count].t = ((-b + sqrt(discriminant)) / (2.0 * a));
	list->inters[list->count].obj = sphere;
	list->count++;
	return (0);
}
