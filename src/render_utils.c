
#include "minirt.h"

int	is_debug_pixel(int i, int j)
{
	if (i == DEBUG_PIXEL_I && j == DEBUG_PIXEL_J)
		return (1);
	return (0);
}

t_inter	get_inter(void)
{
	t_inter	inter;

	ft_memset(&inter, 0, sizeof(t_inter));
	return (inter);
}



// expects a sorted list!
t_inter	*get_hit(t_inter_list *lst)
{
	int			i;
	t_inter	*smallest;
	bool		isset;

	i = 0;
	isset = false;
	smallest = NULL;
	while (i < lst->count)
	{
		if (lst->inters[i].t > 0 && (!isset || lst->inters[i].t < smallest->t))
		{
			smallest = &lst->inters[i];
			isset = 1;
		}
		i++;
	}
	if (!isset)
		return (NULL);
	return (smallest);
}
