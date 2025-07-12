#include "minirt.h"

void	cam_light_alloc(t_minirt *minirt)
{
	minirt->scene->ambient = malloc(sizeof(t_ambient));
	if (!minirt->scene->ambient)
		quit(minirt, MALLOC_ERR);
	minirt->scene->light = malloc(sizeof(t_light));
	if (!minirt->scene->light)
		quit(minirt, MALLOC_ERR);
	minirt->scene->camera = malloc(sizeof(t_camera));
	if (!minirt->scene->camera)
		quit(minirt, MALLOC_ERR);
}

void	spheres_alloc(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	minirt->scene->spheres
		= malloc(sizeof(t_sphere *) * (scene->nb_sphere + 1));
	if (!scene->spheres && scene->nb_sphere)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_sphere)
	{
		scene->spheres[i] = malloc(sizeof(t_sphere));
		if (!scene->spheres[i])
		{
			while (--i >= 0)
				free(scene->spheres[i]);
			quit(minirt, MALLOC_ERR);
		}
	}
	scene->spheres[i] = NULL;
}

void	planes_alloc(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	scene->planes = malloc(sizeof(t_plane *) * (scene->nb_plane + 1));
	if (!scene->planes && scene->nb_plane)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_plane)
	{
		scene->planes[i] = malloc(sizeof(t_plane));
		if (!scene->planes[i])
		{
			while (--i >= 0)
				free(scene->planes[i]);
			quit(minirt, MALLOC_ERR);
		}
	}
	scene->planes[i] = NULL;
}

void	cylinders_alloc(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	scene->cylinders = malloc(sizeof(t_cylinder *) * (scene->nb_cylinder + 1));
	if (!scene->cylinders && scene->nb_cylinder)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_cylinder)
	{
		scene->cylinders[i] = malloc(sizeof(t_cylinder));
		if (!scene->cylinders[i])
		{
			while (--i >= 0)
				free(scene->cylinders[i]);
			quit(minirt, MALLOC_ERR);
		}
	}
	scene->cylinders[i] = NULL;
}

void	alloc_elements(t_minirt *minirt, t_scene *scene)
{
	cam_light_alloc(minirt);
	spheres_alloc(minirt, scene);
	planes_alloc(minirt, scene);
	cylinders_alloc(minirt, scene);
	objects_alloc(minirt, scene);
}
