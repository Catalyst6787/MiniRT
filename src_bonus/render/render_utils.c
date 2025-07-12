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

t_vec3	get_reflection(t_vec3 in, t_vec3 normal)
{
	t_vec3	res;

	res = vec3_double_multiplication(normal, 2);
	res = vec3_double_multiplication(res, vec3_dot(in, normal));
	return (vec3_vec_substraction(in, res));
}

t_ray	get_origin_direction(t_camera camera, t_vec3 pixel)
{
	t_vec3	origin;
	t_vec3	direction;

	origin = vec3_matrix_multiply(camera.inv, get_point3(0, 0, 0));
	direction = vec3_normalise(vec3_vec_substraction(pixel, origin));
	return (get_ray(origin, direction));
}

void	put_pixel(t_minirt *minirt, int color, int x, int y)
{
	int	x_off;
	int	y_off;

	y_off = y;
	while (y_off < y + minirt->render->pixel_size
		&& y_off < minirt->scene->camera->vsize)
	{
		x_off = x;
		while (x_off < x + minirt->render->pixel_size
			&& x_off < minirt->scene->camera->hsize)
		{
			my_mlx_pixel_put(minirt, x_off, y_off, color);
			x_off++;
		}
		y_off++;
	}
}
