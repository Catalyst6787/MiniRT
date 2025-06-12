#include "minirt.h"

int	test_render_scene(t_minirt *minirt)
{
	int		i;
	int		j;
	t_ray	original_ray;
	int		wall_distance;
	int		wall_size;
	int		canva_size;
	int		pixel_size;
	int		half;
	int		world_y;
	int		world_x;
	t_vec3	wall_point;
	t_ray	r;
	t_inter	inter;
	t_sphere	*sphere;

	wall_distance = 10;
	wall_size = 7;
	canva_size = 100;
	pixel_size = wall_size / canva_size;
	half = wall_size / 2;

	sphere = new_sphere(get_point3(0, 0, 0), 2, get_color(1, 0, 0));

	i = 0;
	j = 0;
	original_ray = get_ray(get_vec3(0, 0, -5), get_vec3(0, 0, 1));

	while (i < canva_size)
	{
		j = 0;
		world_y = half - pixel_size * i;
		while (j < canva_size)
		{
			world_x = half - pixel_size * j;
			wall_point = get_point3(world_x, world_y, wall_distance);

			r = get_ray(original_ray.origin, vec3_normalise(vec3_vec_substraction(wall_point, original_ray.origin)));
			inter = get_sphere_inter(sphere, r);
			if (!inter.count)
				my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(0, 0, 255)));
			else
				my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(255, 0, 0)));
			j++;
		}
		i++;
	}
	return (0);
}