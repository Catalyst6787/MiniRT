#include "minirt.h"

t_material	get_material(void)
{
	t_material	empty_material;

	ft_memset(&empty_material, 0, sizeof(t_material));
	return (empty_material);
}

t_material	get_default_material(t_vec3 color, t_scene *scene)
{
	t_material	material;

	(void) scene;
	ft_memset(&material, 0, sizeof(t_material));
	material.color = color;
	material.color.w = 0;
	material.ambient = 0.1;
	material.ambient_color = get_color(1, 1, 1);
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}
