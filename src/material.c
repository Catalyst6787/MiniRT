#include "minirt.h"

t_material	get_material(void)
{
	t_material	empty_material;

	ft_memset(&empty_material, 0, sizeof(t_material));
	return (empty_material);
}

t_material	get_default_material(t_vec3 color)
{
	t_material	material;

	material = get_material();
	material.color = color;
	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}
