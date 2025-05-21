
#include "minirt.h"

t_vec3	*vec3_default_alloc(void)
{
	t_vec3	*vec3;

	vec3 = malloc(sizeof(t_vec3));
	if (!vec3)
		return (perror("Malloc error in vec3_default_alloc()\n"), NULL);
	vec3->x = 0;
	vec3->y = 0;
	vec3->z = 0;
	return (vec3);
}

t_vec3	*vec3_new_alloc(const double x, const double y, const double z)
{
	t_vec3	*vec3;

	vec3 = malloc(sizeof(t_vec3));
	if (!vec3)
		return (perror("Malloc error in vec3_new_alloc()\n"), NULL);
	vec3->x = x;
	vec3->y = y;
	vec3->z = z;
	return (vec3);
}

t_vec3	*vec3_dup_alloc(t_vec3 *to_dup)
{
	t_vec3	*vec3;

	if (!to_dup)
		return (ft_printf("vec3_dup_alloc. Error, passed NULL ptr.\n"), NULL);
	vec3 = malloc(sizeof(t_vec3));
	if (!vec3)
		return (perror("Malloc error in vec3_dup_alloc()\n"), NULL);
	vec3->x = to_dup->x;
	vec3->y = to_dup->y;
	vec3->z = to_dup->z;
	return (vec3);
}

