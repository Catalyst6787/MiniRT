#include "minirt.h"

void	swap_doubles(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_vec3	convert_dir_to_euler(t_vec3 dir)
{
	t_vec3	euler_angles;
	double	len_xz;

	dir = vec3_normalise(dir);
	euler_angles.y = atan2(dir.x, dir.z);
	len_xz = sqrt(dir.x * dir.x + dir.z * dir.z);
	if (len_xz < EPSILON)
	{
		if (dir.y > 0)
			euler_angles.x = M_PI_2;
		else
			euler_angles.x = -M_PI_2;
	}
	else
		euler_angles.x = atan2(dir.y, len_xz);
	euler_angles.z = 0.0;
	return (euler_angles);
}

/** Convert object type enum to string, the selected boolean
 * is used to display "Selected : " before the type (used
 * to print object selected window)
 */
char	*object_type_to_str(t_object *object, bool selected)
{
	if (object->type == SPHERE)
	{
		if (selected)
			return (ft_strdup("Selected : sphere "));
		return (ft_strdup("sphere "));
	}
	if (object->type == PLANE)
	{
		if (selected)
			return (ft_strdup("Selected : plane "));
		return (ft_strdup("plane "));
	}
	if (object->type == CYLINDER)
	{
		if (selected)
			return (ft_strdup("Selected : cylinder "));
		return (ft_strdup("cylinder "));
	}
	return (NULL);
}

void	my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = minirt->mlx->img_st->addr + (y * minirt->mlx->line_length + x
				* (minirt->mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		quit(minirt, PIXEL_PUT_ERR);
}

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
}
