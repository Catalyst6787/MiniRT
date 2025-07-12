#include "minirt.h"

void	set_objects_material(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_sphere)
	{
		scene->spheres[i]->material
			= get_default_material(scene->spheres[i]->color, scene);
		i++;
	}
	i = 0;
	while (i < scene->nb_cylinder)
	{
		scene->cylinders[i]->material
			= get_default_material(scene->cylinders[i]->color, scene);
		i++;
	}
	i = 0;
	while (i < scene->nb_plane)
	{
		scene->planes[i]->material
			= get_default_material(scene->planes[i]->color, scene);
		i++;
	}
}
