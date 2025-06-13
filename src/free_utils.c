#include "minirt.h"

void	free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return;
	free_and_null((void **)&sphere);
}

int	free_render(t_render *render)
{
	free(render->inter_list.inters);
	return (0);
}

