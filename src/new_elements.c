#include "minirt.h"
#include "render.h"
#include "vec3.h"
#include <math.h>

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

void	get_pixel_size(t_camera *camera)
{
	double	half_view;
	double	apsect;

	half_view = tan(camera->fov / 2);
	apsect = camera->hsize / camera->vsize;
	if (apsect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / apsect;
	}
	else
	{
		camera->half_height = half_view;
		camera->half_width = half_view / apsect;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}

// up is a point!
t_camera	*new_camera(t_vec3 from, t_vec3 to, t_vec3 up, double fov)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (perror("new_camera. Error\n"), NULL);
	camera->view.from = from;
	camera->view.to = to;
	camera->view.up = up;
	camera->hsize = WIN_H;
	camera->vsize = WIN_W;
	camera->fov = fov;
	get_pixel_size(camera);
	camera->transform = get_orientation_matrix(camera->view);
	return (camera);
}
