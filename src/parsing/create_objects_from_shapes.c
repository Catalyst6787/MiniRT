#include "minirt.h"

void	create_object_from_sphere(t_object *object, t_sphere *sphere)
{
	object->type = SPHERE;
	object->material = sphere->material;
	object->transform = sphere->transform;
	object->inv = sphere->inv;
}

void	create_object_from_plane(t_object *object, t_plane *plane)
{
	object->type = PLANE;
	object->material = plane->material;
	object->transform = plane->transform;
	object->inv = plane->inv;
}

void	create_object_from_cylinder(t_object *object, t_cylinder *cylinder)
{
	object->type = CYLINDER;
	object->material = cylinder->material;
	object->transform = cylinder->transform;
	object->inv = cylinder->inv;
}

void	create_object_list(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < scene->nb_sphere && j < scene->nb_objects)
	{
		create_object_from_sphere(&scene->objects[j], scene->spheres[i]);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_plane && j < scene->nb_objects)
	{
		create_object_from_plane(&scene->objects[j], scene->planes[i]);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_cylinder && j < scene->nb_objects)
	{
		create_object_from_cylinder(&scene->objects[j], scene->cylinders[i]);
		i++;
		j++;
	}
}
