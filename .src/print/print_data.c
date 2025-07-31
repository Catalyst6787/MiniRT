#include "minirt.h"

void	print_vec3(t_vec3 vec, char *vec_name)
{
	printf("%s - x y z w : %.2f %.2f %.2f %d\n",
		vec_name, vec.x, vec.y, vec.z, vec.w);
}

void	print_ray(t_ray r)
{
	printf("Ray Origin : (%.4f, %.4f, %.4f)\n",
		r.origin.x, r.origin.y, r.origin.z);
	printf("Ray Direction : (%.4f, %.4f, %.4f)\n", r.dir.x, r.dir.y, r.dir.z);
}

void	print_camera_data(t_minirt *minirt)
{
	printf("Camera :\n\n");
	printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->camera->view.from.x,
		minirt->scene->camera->view.from.y, minirt->scene->camera->view.from.z);
	printf("	vectors x y z : %.2f %.2f %.2f\n",
		minirt->scene->camera->view.to.x, minirt->scene->camera->view.to.y,
		minirt->scene->camera->view.to.z);
	printf("	FOV : %f\n\n", minirt->scene->camera->fov);
}

void	print_spheres_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_sphere)
	{
		printf("Sphere[%d/%d] :\n\n", i + 1, minirt->scene->nb_sphere);
		printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos.x,
			minirt->scene->spheres[i]->pos.y, minirt->scene->spheres[i]->pos.z);
		printf("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		printf("	r g b : %.2f %.2f %.2f\n\n",
			minirt->scene->spheres[i]->color.r,
			minirt->scene->spheres[i]->color.g,
			minirt->scene->spheres[i]->color.b);
	}
}

void	print_plane_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_plane)
	{
		printf("Plane[%d/%d] :\n\n", i + 1, minirt->scene->nb_plane);
		printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos.x,
			minirt->scene->planes[i]->pos.y, minirt->scene->planes[i]->pos.z);
		printf("	vectors x y z : %.2f %.2f %.2f\n",
			minirt->scene->planes[i]->dir.x, minirt->scene->planes[i]->dir.y,
			minirt->scene->planes[i]->dir.z);
		printf("	r g b : %.2f %.2f %.2f\n\n",
			minirt->scene->planes[i]->color.r,
			minirt->scene->planes[i]->color.g,
			minirt->scene->planes[i]->color.b);
	}
}
