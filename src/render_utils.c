
#include "minirt.h"
#include "vec3.h"

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

t_vec3	get_reflection(t_vec3 in, t_vec3 normal)
{
	t_vec3	res;

	res = vec3_double_multiplication(normal, 2);
	res = vec3_double_multiplication(res, vec3_dot(in, normal));
	return (vec3_vec_substraction(in, res));
}

t_ray	ray_for_pixel(t_camera camera, double px, double py)
{
	double	xoffset = (px + 0.5) * camera.pixel_size;
	double	yoffset = (py + 0.5) * camera.pixel_size;
	double	world_x = camera.half_width - xoffset;
	double	world_y = camera.half_height - yoffset;
	// canva is always a z = -1 from camera. camera is always at 0.0.0.
	t_vec3	pixel = vec3_matrix_multiply(camera.inv, get_point3(world_x, world_y, -1));
	t_vec3	origin = vec3_matrix_multiply(camera.inv, get_point3(0, 0, 0));
	t_vec3	direction = vec3_normalise(vec3_vec_substraction(pixel, origin));
	return (get_ray(origin, direction));
}
