#include "minirt.h"

// Used for events
void	set_object_ambient_light(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_objects)
	{
		scene->objects[i].material.ambient = scene->ambient->brightness;
		i++;
	}
}

void	set_objects_material(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_sphere)
	{
		scene->spheres[i]->material
			= get_default_material(scene->spheres[i]->color, scene);
		scene->spheres[i]->material.ambient = scene->ambient->brightness;
		scene->spheres[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
	i = 0;
	while (i < scene->nb_cylinder)
	{
		scene->cylinders[i]->material
			= get_default_material(scene->cylinders[i]->color, scene);
		scene->cylinders[i]->material.ambient = scene->ambient->brightness;
		scene->cylinders[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
	i = 0;
	while (i < scene->nb_plane)
	{
		scene->planes[i]->material
			= get_default_material(scene->planes[i]->color, scene);
		scene->planes[i]->material.ambient = scene->ambient->brightness;
		scene->planes[i]->material.ambient_color = scene->ambient->color;
		i++;
	}
	i = 0;
	while (i < scene->nb_cone)
	{
		scene->cones[i]->material
			= get_default_material(scene->cones[i]->color, scene);
		i++;
	}
}
