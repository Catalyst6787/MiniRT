// #include "render.h"
#include "minirt.h"
// #include "ray.h"
// #include "vec3.h"
#include <float.h>
#include <math.h>

t_comp	get_computations(t_scene *scene, t_inter *hit, t_ray r)
{
	t_comp		comp;
	const t_sphere	*sphere; // change for object

	ft_memset(&comp, 0, sizeof(comp));
	comp.eyev =  vec3_reverse(r.dir);
	comp.light = *scene->light;
	sphere = (t_sphere *)hit->obj;
	comp.m = sphere->material;
	comp.point = ray_at(hit->t, r);
	comp.normalv = get_sphere_normal_at(hit->obj, comp.point);
	comp.t = hit->t;
	if (vec3_dot(comp.normalv, comp.eyev) < 0)
	{
		comp.inside = true;
		comp.normalv = vec3_reverse(comp.normalv);
	}
	else
		comp.inside = false;
	return (comp);
}

t_vec3	intersect_objects(t_minirt *minirt, t_ray unique_ray)
{
	int				i;
	t_ray			r;
	t_inter			*hit;
	t_comp			comp;

	i = 0;
	while (i < minirt->scene->nb_sphere)
	{
		r = ray_transform(unique_ray, minirt->scene->spheres[i]->inv);
		get_sphere_inter(minirt->scene->spheres[i],
			r, &minirt->render->inter_list);
		i++;
	}
	i = 0;
	sort_inter(&minirt->render->inter_list);
	hit = get_hit(&minirt->render->inter_list);
	if (!hit)
		return (minirt->render->inter_list.count = 0, get_color(0, 0, 0));
	else
	{
		comp = get_computations(minirt->scene, hit, unique_ray);
		return (minirt->render->inter_list.count = 0 ,get_lighting(comp));
	}
	minirt->render->inter_list.count = 0;
}

int	render_scene(t_minirt *minirt)
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	if (!minirt)
		quit(minirt, "render_scene: NULL prt!");
	print_camera_data(minirt);
	while (y < minirt->scene->camera->vsize - 1)
	{
		x = 0;
		while(x < minirt->scene->camera->hsize - 1)
		{
			ray = ray_for_pixel(*minirt->scene->camera, x, y);
			my_mlx_pixel_put(minirt, x, y, color_to_int(intersect_objects(minirt, ray)));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	return (0);
}
