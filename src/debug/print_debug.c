
#include "minirt.h"

void	print_render_data(t_render *render)
{
	(void)render;
	PRINT_DEBUG("focal_length:				%.2f\n", render->focal_length);
	PRINT_DEBUG("double	viewport_height:	%.2f\n", render->viewport_height);
	PRINT_DEBUG("double	viewport_width:		%.2f\n", render->viewport_width);
	PRINT_DEBUG("camera_center :				(%.3f, %.3f, %.3f)\n", render->camera_center.x, render->camera_center.y, render->camera_center.z);
	PRINT_DEBUG("camera_dir :				(%.3f, %.3f, %.3f)\n", render->camera_dir.x, render->camera_dir.y, render->camera_dir.z);
	PRINT_DEBUG("world_up :					(%.3f, %.3f, %.3f)\n", render->world_up.x, render->world_up.y, render->world_up.z);
	PRINT_DEBUG("right :						(%.3f, %.3f, %.3f)\n", render->right.x, render->right.y, render->right.z);
	PRINT_DEBUG("up :						(%.3f, %.3f, %.3f)\n", render->up.x, render->up.y, render->up.z);
	PRINT_DEBUG("viewport_u :				(%.3f, %.3f, %.3f)\n", render->viewport_u.x, render->viewport_u.y, render->viewport_u.z);
	PRINT_DEBUG("viewport_v :				(%.3f, %.3f, %.3f)\n", render->viewport_v.x, render->viewport_v.y, render->viewport_v.z);
	PRINT_DEBUG("pixel_delta_u :				(%.3f, %.3f, %.3f)\n", render->pixel_delta_u.x, render->pixel_delta_u.y, render->pixel_delta_u.z);
	PRINT_DEBUG("pixel_delta_v :				(%.3f, %.3f, %.3f)\n", render->pixel_delta_v.x, render->pixel_delta_v.y, render->pixel_delta_v.z);
	PRINT_DEBUG("viewport_upper_left :		(%.3f, %.3f, %.3f)\n", render->viewport_upper_left.x, render->viewport_upper_left.y, render->viewport_upper_left.z);
	PRINT_DEBUG("pixel00_loc:				(%.3f, %.3f, %.3f)\n", render->pixel00_loc.x, render->pixel00_loc.y, render->pixel00_loc.z);
	PRINT_DEBUG("\n\n");
}
void	print_render_pixel(t_vec3	pixel_center,
	t_vec3	ray_direction,
	t_ray	ray,
	t_vec3	ray_or,
	t_vec3	ray_dir,
	t_vec3	color)
{
	PRINT_DEBUG("Pixel center : (%.3f, %.3f, %.3f)\n", pixel_center.x, pixel_center.y, pixel_center.z);
	PRINT_DEBUG("Ray direction : (%.3f, %.3f, %.3f)\n", ray_direction.x, ray_direction.y, ray_direction.z);
	PRINT_DEBUG("ray : (%.3f, %.3f, %.3f)\n", ray.dir->x, ray.dir->y, ray.dir->z); 
	PRINT_DEBUG("ray or : (%.3f, %.3f, %.3f)\n", ray_or.x, ray_or.y, ray_or.z);
	PRINT_DEBUG("ray_dir : (%.3f, %.3f, %.3f)\n", ray_dir.x, ray_dir.y, ray_dir.z);
	PRINT_DEBUG("color : (%.3f, %.3f, %.3f)\n", color.x, color.y, color.z);
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
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->ambient->color->r,minirt->scene->ambient->color->g, minirt->scene->ambient->color->b);
	PRINT_DEBUG("Camera :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->camera->pos->x, minirt->scene->camera->pos->y, minirt->scene->camera->pos->z);
	PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->camera->dir->x, minirt->scene->camera->dir->y, minirt->scene->camera->dir->z);
	PRINT_DEBUG("	FOV : %d\n\n", minirt->scene->camera->fov);
	PRINT_DEBUG("Light(s) :\n\n");
	PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->light->pos->x, minirt->scene->light->pos->y, minirt->scene->light->pos->z);
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->light->brightness);
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->light->color->r, minirt->scene->light->color->g, minirt->scene->light->color->b);
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Sphere[%d/%d] :\n\n", i + 1, minirt->scene->nb_sphere);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos->x, minirt->scene->spheres[i]->pos->y, minirt->scene->spheres[i]->pos->z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->spheres[i]->color->r, minirt->scene->spheres[i]->color->g, minirt->scene->spheres[i]->color->b);
	}
	i = -1;
	while (++i < minirt->scene->nb_plane)
	{
		PRINT_DEBUG("Plane[%d/%d] :\n\n", i + 1, minirt->scene->nb_plane);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos->x, minirt->scene->planes[i]->pos->y, minirt->scene->planes[i]->pos->z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->planes[i]->dir->x, minirt->scene->planes[i]->dir->y, minirt->scene->planes[i]->dir->z);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->planes[i]->color->r, minirt->scene->planes[i]->color->g, minirt->scene->planes[i]->color->b);
	}
	i = -1;
	while (++i < minirt->scene->nb_cylinder)
	{
		PRINT_DEBUG("Cylinder[%d/%d] :\n\n", i + 1, minirt->scene->nb_cylinder);
		PRINT_DEBUG("	x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->pos->x, minirt->scene->cylinders[i]->pos->y, minirt->scene->cylinders[i]->pos->z);
		PRINT_DEBUG("	vectors x y z : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->dir->x, minirt->scene->cylinders[i]->dir->y, minirt->scene->cylinders[i]->dir->z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->cylinders[i]->diameter);
		PRINT_DEBUG("	Height : %.2f\n", minirt->scene->cylinders[i]->height);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->cylinders[i]->color->r, minirt->scene->cylinders[i]->color->g, minirt->scene->cylinders[i]->color->b);
	}
	PRINT_DEBUG("\n");
	// PRINT_DEBUG("	aspect_ratio = [%f]\n", minirt->aspect_ratio);
	// PRINT_DEBUG("	img_width = [%d]\n", minirt->img_width);
	// PRINT_DEBUG("	img_height = [%d]\n", minirt->img_height);
	// PRINT_DEBUG("	viewport_width = [%f]\n", minirt->view_width);
	// PRINT_DEBUG("	viewport_height = [%f]\n\n", minirt->view_height);
}


