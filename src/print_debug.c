
#include "minirt.h"

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

void	print_scene_ok_message()
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
	PRINT_DEBUG("	r g b : %d %d %d\n\n", minirt->scene->ambient->color->r,minirt->scene->ambient->color->g, minirt->scene->ambient->color->b);
	PRINT_DEBUG("Camera :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->camera->pos->x, minirt->scene->camera->pos->y, minirt->scene->camera->pos->z);
	PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->camera->dir->x, minirt->scene->camera->dir->y, minirt->scene->camera->dir->z);
	PRINT_DEBUG("	FOV : %d\n\n", minirt->scene->camera->fov);
	PRINT_DEBUG("Light(s) :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->light->pos->x, minirt->scene->light->pos->y, minirt->scene->light->pos->z);
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->light->brightness);
	PRINT_DEBUG("	r g b : %d %d %d\n\n", minirt->scene->light->color->r, minirt->scene->light->color->g, minirt->scene->light->color->b);
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Sphere[%d]) :\n\n", i);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos->x, minirt->scene->spheres[i]->pos->y, minirt->scene->spheres[i]->pos->z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		PRINT_DEBUG("	r g b : %d %d %d\n\n", minirt->scene->spheres[i]->color->r, minirt->scene->spheres[i]->color->g, minirt->scene->spheres[i]->color->b);
	}
	i = -1;
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Plane[%d] :\n\n", i);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos->x, minirt->scene->planes[i]->pos->y, minirt->scene->planes[i]->pos->z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->dir->x, minirt->scene->planes[i]->dir->y, minirt->scene->planes[i]->dir->z);
		PRINT_DEBUG("	r g b : %d %d %d\n\n", minirt->scene->planes[i]->color->r, minirt->scene->planes[i]->color->g, minirt->scene->planes[i]->color->b);
	}
	i = -1;
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Cylinder[%d] :\n\n", i);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->pos->x, minirt->scene->cylinders[i]->pos->y, minirt->scene->cylinders[i]->pos->z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->dir->x, minirt->scene->cylinders[i]->dir->y, minirt->scene->cylinders[i]->dir->z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->cylinders[i]->diameter);
		PRINT_DEBUG("	Height : %.2f\n", minirt->scene->cylinders[i]->height);
		PRINT_DEBUG("	r g b : %d %d %d\n\n", minirt->scene->cylinders[i]->color->r, minirt->scene->cylinders[i]->color->g, minirt->scene->cylinders[i]->color->b);
		PRINT_DEBUG("\n");
	}
	// PRINT_DEBUG("	aspect_ratio = [%f]\n", minirt->aspect_ratio);
	// PRINT_DEBUG("	img_width = [%d]\n", minirt->img_width);
	// PRINT_DEBUG("	img_height = [%d]\n", minirt->img_height);
	// PRINT_DEBUG("	viewport_width = [%f]\n", minirt->view_width);
	// PRINT_DEBUG("	viewport_height = [%f]\n\n", minirt->view_height);
}


