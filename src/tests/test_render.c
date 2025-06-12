#include "minirt.h"

t_ray	get_scaled_ray(t_ray r, t_vec3 scaler)
{
	t_ray		ray2;
	t_matrix	m;

	m = get_scaling_matrix(scaler.x, scaler.y, scaler.z);
	ray2 = get_ray(vec3_matrix_multiply(m, r.origin), vec3_matrix_multiply(m, r.dir));

	return( (ray2));
}



int	test_render_scene(t_minirt *minirt)
{
	t_sphere	*sphere;
	int		i;
	int		j;
	t_ray	original_ray;
	double		wall_distance;
	double		wall_size;
	double		canva_size;
	double		pixel_size;
	double		half;
	double		world_y;
	double		world_x;
	t_vec3	wall_point;
	t_ray	r;
	t_inter	inter;

	wall_distance = 10;
	wall_size = 7;
	canva_size = 100;
	pixel_size = wall_size / canva_size;
	half = wall_size / 2;

	
	i = 0;
	j = 0;
	t_vec3 point = get_point3(0, 0, 0);
	t_vec3 col = get_color(1, 0, 0);
	sphere = new_sphere(point, 2, col);
	original_ray = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));
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
			{
				my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(0, 0, 255)));
			}
			else
			{
				my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(255, 0, 0)));
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	free_sphere(sphere);
	return (0);
}
