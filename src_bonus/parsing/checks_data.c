#include "minirt.h"

int	is_ok_color(t_vec3 v)
{
	if (v.r < 0 || 255 < v.r)
		return (0);
	if (v.g < 0 || 255 < v.g)
		return (0);
	if (v.b < 0 || 255 < v.b)
		return (0);
	return (1);
}

int	is_ok_dir(t_vec3 v)
{
	if (v.x < -1 || 1 < v.x)
		return (0);
	if (v.y < -1 || 1 < v.y)
		return (0);
	if (v.z < -1 || 1 < v.z)
		return (0);
	return (1);
}

int	is_ok_ratio(double var)
{
	if (var < 0 || 1 < var)
		return (0);
	return (1);
}

static void	check_elements(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	if (!is_ok_ratio(scene->ambient->brightness)
		|| !is_ok_color(scene->ambient->color))
		quit(minirt, WRONG_AMB_DATA);
	if (scene->camera->fov < 0.0 || 180.0 < scene->camera->fov)
		quit(minirt, WRONG_CAM_DATA);
	while (++i < scene->nb_light)
		if (!is_ok_ratio(scene->lights[i]->brightness)
			|| !is_ok_color(scene->lights[i]->color))
			quit(minirt, WRONG_LIGHT_DATA);
}

void	check_data_validity(t_minirt *minirt, t_scene *scene)
{
	int	i;

	check_elements(minirt, scene);
	i = -1;
	while (++i < scene->nb_sphere)
		if (!is_ok_color(scene->spheres[i]->color))
			quit(minirt, WRONG_SPH_DATA);
	i = -1;
	while (++i < scene->nb_plane)
		if (!is_ok_dir(scene->planes[i]->dir)
			|| !is_ok_color(scene->planes[i]->color))
			quit(minirt, WRONG_PLANE_DATA);
	i = -1;
	while (++i < scene->nb_cylinder)
		if (!is_ok_dir(scene->cylinders[i]->dir)
			|| !is_ok_color(scene->cylinders[i]->color))
			quit(minirt, WRONG_CYL_DATA);
	i = -1;
	while (++i < scene->nb_cone)
		if (!is_ok_dir(scene->cones[i]->dir)
			|| !is_ok_color(scene->cones[i]->color))
			quit(minirt, WRONG_CONE_DATA);
}
