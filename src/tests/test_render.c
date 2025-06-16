#include "minirt.h"

t_ray	get_scaled_ray(t_ray r, t_vec3 scaler)
{
	t_ray		scaled_ray;
	t_matrix	m;

	m = get_scaling_matrix(scaler);
	m = get_inversed_matrix(m);
	scaled_ray = get_ray(vec3_matrix_multiply(m, r.origin), vec3_matrix_multiply(m, r.dir));

	return(scaled_ray);
}

t_ray	get_translated_ray(t_ray r, t_vec3 translater)
{
	t_ray		translated_ray;
	t_matrix	m;
	m = get_translation_matrix(translater);
	m = get_inversed_matrix(m);
	translated_ray = get_ray(vec3_matrix_multiply(m, r.origin), vec3_matrix_multiply(m, r.dir));
	return (translated_ray);
}

// t_ray	get_sheared_ray(t_ray r, t_vec3 shearer)
// {
// 	t_ray		sheared_ray;
// 	t_matrix	m;
// 	m = get_translation_matrix(translater.x, translater.y, translater.z).;


// }

// int	get_normal_at(t_sphere *sphere, t_vec3 point)
// {
// 	t_vec3	object_normal;
// 	t_vec3	transformed_point;

// 	transformed_point = get




// }

int	test_render_scene(t_minirt *minirt)
{
	t_sphere		*sphere;
	t_sphere		*sphere2;
	t_sphere		*sphere3;
	int				i;
	int				j;
	t_ray			original_ray;
	t_ray			unique_ray;
	double			wall_distance;
	double			wall_size;
	double			canva_height;
	double			canva_width;
	double			pixel_size;
	double			half;
	double			world_y;
	double			world_x;
	t_vec3			wall_point;
	t_ray			r;
	t_inter			inter[6];
	t_inter_list	lst;
	t_matrix		transform;
	t_matrix		transform2;
	t_matrix		transform3;
	t_inter			*hit;

	t_vec3	scaler;
	t_vec3	translater;
	(void)scaler;
	(void)translater;

	lst.capacity = 6;
	lst.count = 0;
	lst.inters = inter;

	wall_distance = 10;
	wall_size = 7;
	canva_width = WIN_H;
	canva_height = WIN_H;
	pixel_size = wall_size / canva_width;
	half = wall_size / 2;


	i = 0;
	j = 0;
	sphere = new_sphere(get_point3(0, 0, 0), 0, get_color(1, 0, 0));
	sphere2 = new_sphere(get_point3(0, 0, 0), 0, get_color(0, 1, 0));
	sphere3 = new_sphere(get_point3(0, 0, 0), 0, get_color(0, 0, 1));

	original_ray = get_ray(get_point3(0, 0, -5), get_vec3(0, 0, 1));

	transform = multiply_matrix(get_translation_matrix(get_vec3(0, 0, 2)), get_rotation_matrix(get_vec3(0, 0, 0.5)));
	transform = multiply_matrix(transform, get_scaling_matrix(get_vec3(0.3, 2, 2)));
	transform = get_inversed_matrix(transform);
	sphere->transform = transform;

	transform2 = multiply_matrix(get_translation_matrix(get_vec3(0, 0, -1)), get_rotation_matrix(get_vec3(0, 0, 0)));
	transform2 = multiply_matrix(transform2, get_scaling_matrix(get_vec3(0.5, 0.5, 0.5)));
	transform2 = get_inversed_matrix(transform2);
	sphere2->transform = transform2;

	transform3 = multiply_matrix(get_translation_matrix(get_vec3(0, 0, -2)), get_rotation_matrix(get_vec3(0, 0, 0)));
	transform3 = multiply_matrix(transform3, get_scaling_matrix(get_vec3(0.1, 0.1, 0.1)));
	transform3 = get_inversed_matrix(transform3);
	sphere3->transform = transform3;

	while (i < canva_height)
	{
		j = 0;
		world_y = half - pixel_size * i;
		while (j < canva_width)
		{
			world_x = half - pixel_size * j;
			wall_point = get_point3(world_x, world_y, wall_distance);
			unique_ray = get_ray(original_ray.origin, vec3_normalise(vec3_vec_substraction(wall_point, original_ray.origin)));
			r = unique_ray;
			r = ray_transform(r, transform);
			get_sphere_inter(sphere, r, &lst);
			r = unique_ray;
			r = ray_transform(r, transform2);
			get_sphere_inter(sphere2, r, &lst);
			r = unique_ray;
			r = ray_transform(r, transform3);
			get_sphere_inter(sphere3, r, &lst);
			// if (!lst.count)
			// {
			// 	my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(0, 0, 255)));
			// }
			// else
			// {
			// 	my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(255, 0, 0)));
			// }
			hit = get_hit(&lst);
			if (!hit)
				my_mlx_pixel_put(minirt, j, i, color_to_int(get_color(0, 0, 0)));

			else
			{
				const t_sphere *intersected_sphere = hit->obj;
				my_mlx_pixel_put(minirt, j, i, color_to_int(intersected_sphere->color));
			}
			j++;
			lst.count = 0;
		}
		i++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	free_sphere(sphere);
	free_sphere(sphere2);
	free_sphere(sphere3);
	return (0);
}
