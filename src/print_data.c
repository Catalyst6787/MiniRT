#include "minirt.h"

void	print_vec3(t_vec3 vec, char *vec_name)
{
	printf("%s - x y z w : %.2f %.2f %.2f %d\n", vec_name, vec.x, vec.y, vec.z, vec.w);
}

void	print_ray(t_ray r)
{
	printf("Ray Origin : (%.4f, %.4f, %.4f)\n", r.origin.x, r.origin.y, r.origin.z);
	printf("Ray Direction : (%.4f, %.4f, %.4f)\n", r.dir.x, r.dir.y, r.dir.z);
}

void	print_camera_data(t_minirt *minirt)
{
	printf("Camera :\n\n");
	printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->camera->view.from.x, minirt->scene->camera->view.from.y, minirt->scene->camera->view.from.z);
	printf("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->camera->view.to.x, minirt->scene->camera->view.to.y, minirt->scene->camera->view.to.z);
	printf("	FOV : %f\n\n", minirt->scene->camera->fov);
}

void	print_spheres_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_sphere)
	{
		printf("Sphere[%d/%d] :\n\n", i + 1, minirt->scene->nb_sphere);
		printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos.x, minirt->scene->spheres[i]->pos.y, minirt->scene->spheres[i]->pos.z);
		printf("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		printf("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->spheres[i]->color.r, minirt->scene->spheres[i]->color.g, minirt->scene->spheres[i]->color.b);
	}
}

void	print_plane_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_plane)
	{
		printf("Plane[%d/%d] :\n\n", i + 1, minirt->scene->nb_plane);
		printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos.x, minirt->scene->planes[i]->pos.y, minirt->scene->planes[i]->pos.z);
		printf("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->dir.x, minirt->scene->planes[i]->dir.y, minirt->scene->planes[i]->dir.z);
		printf("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->planes[i]->color.r, minirt->scene->planes[i]->color.g, minirt->scene->planes[i]->color.b);
	}
}

void	print_cylinder_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_cylinder)
	{
		printf("Cylinder[%d/%d] :\n\n", i + 1, minirt->scene->nb_cylinder);
		printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->pos.x, minirt->scene->cylinders[i]->pos.y, minirt->scene->cylinders[i]->pos.z);
		printf("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->dir.x, minirt->scene->cylinders[i]->dir.y, minirt->scene->cylinders[i]->dir.z);
		printf("	Diameter : %.2f\n", minirt->scene->cylinders[i]->diameter);
		printf("	Height : %.2f\n", minirt->scene->cylinders[i]->height);
		printf("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->cylinders[i]->color.r, minirt->scene->cylinders[i]->color.g, minirt->scene->cylinders[i]->color.b);
	}
}

void	event_print_debug(t_minirt *minirt)
{
	printf("\n");
	printf("Ambiant light :\n\n");
	printf("	Ratio : %.2f\n", minirt->scene->ambient->brightness);
	printf("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->ambient->color.r,minirt->scene->ambient->color.g, minirt->scene->ambient->color.b);
	print_camera_data(minirt);
	printf("Light(s) :\n\n");
	printf("	x y z : %.2f %.2f %.2f\n", minirt->scene->light->pos.x, minirt->scene->light->pos.y, minirt->scene->light->pos.z);
	printf("	Ratio : %.2f\n", minirt->scene->light->brightness);
	printf("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->light->color.r, minirt->scene->light->color.g, minirt->scene->light->color.b);
	print_spheres_data(minirt);
	print_plane_data(minirt);
	print_cylinder_data(minirt);
}

void	print_inter(t_inter *inter)
{
	printf("inter: t=[%f], obj=[%p]\n", inter->t, (void *)inter->obj);
}

void	print_scene(t_minirt *minirt, bool asterix)
{
	if (asterix == true)
	{
		printf("\n* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("*                  Scene                  *");
		printf("\n\n");
	}
	printf("\n");
	printf("%s", minirt->scene->buffer);
	printf("\n");
	if (asterix == true)
	{
		printf("\n\n");
		printf("*                                         *\n");
		printf("* * * * * * * * * * * * * * * * * * * * * *\n\n");
	}
}

void	print_inter_list(t_inter_list *list)
{
	int	i;

	i = 0;
	printf("Inter Count %d\n", list->count);
	while (i < list->count)
	{
		printf("Inter obj [%d] : %p\n", i, (void *)list->inters[i].obj);
		printf("Inter  [%d] : %.3f\n", i, list->inters[i].t);
		i++;
	}

}
