#include "minirt.h"

void	free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return;
	free(sphere->pos);
	free(sphere->color);
	free_and_null((void **)&sphere);
}

int	free_render(t_render *render)
{
	if (!render)
		return (ft_printf("Error. free_render: got passed null pointer"), 1);
	if (render->camera_center)
		free(render->camera_center);
	render->camera_center = NULL;
	if (render->viewport_u)
		free(render->viewport_u);
	render->viewport_u = NULL;
	if (render->viewport_v)
		free(render->viewport_v);
	render->viewport_v = NULL;
	if (render->pixel_delta_u)
		free(render->pixel_delta_u);
	render->pixel_delta_u = NULL;
	if (render->pixel_delta_v)
		free(render->pixel_delta_v);
	render->pixel_delta_v = NULL;
	if (render->viewport_upper_left)
		free(render->viewport_upper_left);
	render->viewport_upper_left = NULL;
	if (render->pixel00_loc)
		free(render->pixel00_loc);
	render->pixel00_loc = NULL;
	free_and_null((void **)&render);
	return (0);
}

