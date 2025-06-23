#include "minirt.h"

t_light	*new_light(t_vec3 pos, t_vec3 color)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (perror("new_light. Error\n"), NULL);
	light->pos.x = pos.x;
	light->pos.y = pos.y;
	light->pos.z = pos.z;
	light->pos.w = 1;
	light->color.x = color.x;
	light->color.y = color.y;
	light->color.z = color.z;
	light->brightness = 1;
	return (light);
}

t_ambient	*new_ambiant(t_vec3 color)
{
	t_ambient	*ambient;

	ambient = ft_calloc(1, sizeof(t_ambient));
	if (!ambient)
		return (perror("new_ambient. Error\n"), NULL);
	ambient->color.x = color.x;
	ambient->color.y = color.y;
	ambient->color.z = color.z;
	ambient->brightness = 0;
	return (ambient);
}

t_camera	*new_camera(t_vec3 pos, t_vec3 dir)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (perror("new_camera. Error\n"), NULL);
	camera->pos.x = pos.x;
	camera->pos.y = pos.y;
	camera->pos.z = pos.z;
	camera->pos.w = 1;
	camera->dir.x = dir.x;
	camera->dir.y = dir.y;
	camera->dir.z = dir.z;
	camera->dir.w = 0;
	return (camera);
}
