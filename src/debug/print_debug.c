
#include "minirt.h"

void	print_render_data(t_render *render)
{
	(void)render;
	// PRINT_DEBUG("\n\n");
}
void	print_render_pixel(t_vec3	pixel_center,
	t_vec3	ray_direction,
	t_ray	ray,
	t_vec3	color)
{
	PRINT_DEBUG("Pixel center :				(%.3f, %.3f, %.3f)\n", pixel_center.x, pixel_center.y, pixel_center.z);
	PRINT_DEBUG("Ray direction :				(%.3f, %.3f, %.3f)\n", ray_direction.x, ray_direction.y, ray_direction.z);
	PRINT_DEBUG("ray dir :					(%.3f, %.3f, %.3f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
	PRINT_DEBUG("ray origin :				(%.3f, %.3f, %.3f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
	PRINT_DEBUG("color :						(%.3f, %.3f, %.3f)\n", color.x, color.y, color.z);
	PRINT_DEBUG("\n\n");
}

void	debug_print_inter(t_inter inter)
{
	printf("inter: t=[%f], obj=[%p]\n", inter.t, inter.obj);
}

void	debug_print_inter_list(t_inter_list lst)
{
	int	i;

	i = 0;
	printf("inter_lst of size %d:\n", lst.count);
	while (i < lst.count)
	{
		printf("inter [%d]:	", i);
		debug_print_inter(lst.inters[i]);
		i++;
	}

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

void	print_scene_ok_message(void)
{
	printf("%sScene OK%s\n\n", GREEN, COLOR_RESET);
	printf("--------------------------\n\n");
}


void	print_scene_data(t_minirt *minirt)
{
	int i = -1;
	PRINT_DEBUG("\n* * * * * * * * * * * * * * * * * * * * * *\n");
	PRINT_DEBUG("*                  Scene                  *");
	PRINT_DEBUG("\n\n");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("%s", minirt->scene->buffer);
	PRINT_DEBUG("\n");
	PRINT_DEBUG("\n\n");
	PRINT_DEBUG("*                                         *\n");
	PRINT_DEBUG("* * * * * * * * * * * * * * * * * * * * * *\n\n");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("Ambiant light :\n\n");
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->ambient->brightness);
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->ambient->color.r,minirt->scene->ambient->color.g, minirt->scene->ambient->color.b);
	PRINT_DEBUG("Camera :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->camera->pos.x, minirt->scene->camera->pos.y, minirt->scene->camera->pos.z);
	PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->camera->dir.x, minirt->scene->camera->dir.y, minirt->scene->camera->dir.z);
	PRINT_DEBUG("	FOV : %d\n\n", minirt->scene->camera->fov);
	PRINT_DEBUG("Light(s) :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->light->pos.x, minirt->scene->light->pos.y, minirt->scene->light->pos.z);
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->light->brightness);
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->light->color.r, minirt->scene->light->color.g, minirt->scene->light->color.b);
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Sphere[%d/%d] :\n\n", i + 1, minirt->scene->nb_sphere);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos.x, minirt->scene->spheres[i]->pos.y, minirt->scene->spheres[i]->pos.z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->spheres[i]->material.color.r, minirt->scene->spheres[i]->material.color.g, minirt->scene->spheres[i]->material.color.b);
	}
	i = -1;
	while (++i < minirt->scene->nb_plane)
	{
		PRINT_DEBUG("Plane[%d/%d] :\n\n", i + 1, minirt->scene->nb_plane);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos.x, minirt->scene->planes[i]->pos.y, minirt->scene->planes[i]->pos.z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->dir.x, minirt->scene->planes[i]->dir.y, minirt->scene->planes[i]->dir.z);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->planes[i]->material.color.r, minirt->scene->planes[i]->material.color.g, minirt->scene->planes[i]->material.color.b);
	}
	i = -1;
	while (++i < minirt->scene->nb_cylinder)
	{
		PRINT_DEBUG("Cylinder[%d/%d] :\n\n", i + 1, minirt->scene->nb_cylinder);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->pos.x, minirt->scene->cylinders[i]->pos.y, minirt->scene->cylinders[i]->pos.z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->dir.x, minirt->scene->cylinders[i]->dir.y, minirt->scene->cylinders[i]->dir.z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->cylinders[i]->diameter);
		PRINT_DEBUG("	Height : %.2f\n", minirt->scene->cylinders[i]->height);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->cylinders[i]->material.color.r, minirt->scene->cylinders[i]->material.color.g, minirt->scene->cylinders[i]->material.color.b);
	}
	i = 0;
	while (i < minirt->scene->nb_objects)
	{
		PRINT_DEBUG("object type: %d\n", minirt->scene->objects[i].type);
		i++;
	}
	PRINT_DEBUG("\n");
	// PRINT_DEBUG("	aspect_ratio = [%f]\n", minirt->aspect_ratio);
	// PRINT_DEBUG("	img_width = [%d]\n", minirt->img_width);
	// PRINT_DEBUG("	img_height = [%d]\n", minirt->img_height);
	// PRINT_DEBUG("	viewport_width = [%f]\n", minirt->view_width);
	// PRINT_DEBUG("	viewport_height = [%f]\n\n", minirt->view_height);
}


