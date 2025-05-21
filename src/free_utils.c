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
	(void)render;
	return (0);
}

