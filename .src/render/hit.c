#include "minirt.h"

t_inter	*get_hit(t_inter_list *lst)
{
	int	i;

	i = 0;
	while (i < lst->count)
	{
		if (lst->inters[i].t > 0)
			return (&lst->inters[i]);
		i++;
	}
	return (NULL);
}
