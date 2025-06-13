#include "minirt.h"

static void	set_spheres_transformation(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_sphere)
	{
		set_sphere_transformation(scene->spheres[i]);
		i++;
	}
}

static void	set_planes_transformation(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_plane)
	{
		set_plane_transformation(scene->planes[i]);
		i++;
	}
}

// shearing not implemented
static void	set_cylinders_transformation(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_cylinder)
	{
		set_cylinder_tranformation(scene->cylinders[i]);
		i++;
	}
}

void	set_objects_transformation(t_scene *scene)
{
	set_spheres_transformation(scene);
	set_planes_transformation(scene);
	set_cylinders_transformation(scene);
}
