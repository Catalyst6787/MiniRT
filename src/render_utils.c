
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
	int		i;
	t_inter	*smallest;
	bool	isset;

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

t_vec3	get_normal_at(t_sphere *s, t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	object_normal;
	t_vec3	world_normal;

	object_point = vec3_matrix_multiply(s->inv, world_point);
	object_normal = vec3_vec_substraction(object_point, get_point3(0, 0, 0));
	world_normal = vec3_matrix_multiply(
			transpose_matrix(s->inv), object_normal);
	world_normal.w = 0;
	return (vec3_normalise(world_normal));
}
