#include "minirt.h"

void	print_render_data(t_render *render)
{
	(void)render;
}

void	debug_print_ray(t_ray *r)
{
	PRINT_DEBUG("Ray Origin : (%.4f, %.4f, %.4f)\n", r->origin.x, r->origin.y, r->origin.z);
	PRINT_DEBUG("Ray Direction : (%.4f, %.4f, %.4f)\n", r->dir.x, r->dir.y, r->dir.z);
}

void	debug_print_vec(t_vec3 *v, char *name)
{
	PRINT_DEBUG("Vector %s : ", name);
	PRINT_DEBUG("(%.4f, %.4f, %.4f) ", v->x, v->y, v->z);
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


void	print_scene_ok_message(char *scene)
{
	printf("%s\n%s : scene OK!%s\n\n", GREEN, scene, COLOR_RESET);
	printf("--------------------------\n\n");
}


void	debug_print_scene_data(t_minirt *minirt)
{
	int i = -1;
	PRINT_DEBUG("\n* * * * * * * * * * * * * * * * * * * * * *\n");
	PRINT_DEBUG("*                  Scene                  *");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("%s", minirt->scene->buffer);
	PRINT_DEBUG("\n");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("*                                         *\n");
	PRINT_DEBUG("* * * * * * * * * * * * * * * * * * * * * *\n\n");
	PRINT_DEBUG("\n");
	PRINT_DEBUG("Ambiant light :\n\n");
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->ambient->brightness);
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->ambient->color.r,minirt->scene->ambient->color.g, minirt->scene->ambient->color.b);
	PRINT_DEBUG("Camera :\n\n");
	PRINT_DEBUG("	pos : %.2f %.2f %.2f\n", minirt->scene->camera->view.from.x, minirt->scene->camera->view.from.y, minirt->scene->camera->view.from.z);
	PRINT_DEBUG("	dir : %.2f %.2f %.2f\n", minirt->scene->camera->view.to.x, minirt->scene->camera->view.to.y, minirt->scene->camera->view.to.z);
	PRINT_DEBUG("	FOV : %f\n\n", minirt->scene->camera->fov);
	PRINT_DEBUG("Light(s) :\n\n");
	PRINT_DEBUG("	pos : %.2f %.2f %.2f\n", minirt->scene->light->pos.x, minirt->scene->light->pos.y, minirt->scene->light->pos.z);
	PRINT_DEBUG("	Ratio : %.2f\n", minirt->scene->light->brightness);
	PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->light->color.r, minirt->scene->light->color.g, minirt->scene->light->color.b);
	while (++i < minirt->scene->nb_sphere)
	{
		PRINT_DEBUG("Sphere[%d/%d] :\n\n", i + 1, minirt->scene->nb_sphere);
		PRINT_DEBUG("	pos : %.2f %.2f %.2f\n", minirt->scene->spheres[i]->pos.x, minirt->scene->spheres[i]->pos.y, minirt->scene->spheres[i]->pos.z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->spheres[i]->diameter);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->spheres[i]->material.color.r, minirt->scene->spheres[i]->material.color.g, minirt->scene->spheres[i]->material.color.b);
	}
	i = -1;
	while (++i < minirt->scene->nb_plane)
	{
		PRINT_DEBUG("Plane[%d/%d] :\n\n", i + 1, minirt->scene->nb_plane);
		PRINT_DEBUG("	pos : %.2f %.2f %.2f\n", minirt->scene->planes[i]->pos.x, minirt->scene->planes[i]->pos.y, minirt->scene->planes[i]->pos.z);
		PRINT_DEBUG("	dir : %.2f %.2f %.2f\n", minirt->scene->planes[i]->dir.x, minirt->scene->planes[i]->dir.y, minirt->scene->planes[i]->dir.z);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->planes[i]->material.color.r, minirt->scene->planes[i]->material.color.g, minirt->scene->planes[i]->material.color.b);
	}
	i = -1;
	while (++i < minirt->scene->nb_cylinder)
	{
		PRINT_DEBUG("Cylinder[%d/%d] :\n\n", i + 1, minirt->scene->nb_cylinder);
		PRINT_DEBUG("	pos : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->pos.x, minirt->scene->cylinders[i]->pos.y, minirt->scene->cylinders[i]->pos.z);
		PRINT_DEBUG("	dir : %.2f %.2f %.2f\n", minirt->scene->cylinders[i]->dir.x, minirt->scene->cylinders[i]->dir.y, minirt->scene->cylinders[i]->dir.z);
		PRINT_DEBUG("	Diameter : %.2f\n", minirt->scene->cylinders[i]->diameter);
		PRINT_DEBUG("	Height : %.2f\n", minirt->scene->cylinders[i]->height);
		PRINT_DEBUG("	r g b : %.2f %.2f %.2f\n\n", minirt->scene->cylinders[i]->material.color.r, minirt->scene->cylinders[i]->material.color.g, minirt->scene->cylinders[i]->material.color.b);
	}
	i = 0;
	PRINT_DEBUG("\n");
}

void	debug_print_objects_pointers(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	PRINT_DEBUG("Objects pointers :\n\n");
	while (i < scene->nb_sphere && j < scene->nb_objects)
	{
		PRINT_DEBUG("Sphere[%d] : %p (object %d)\n", i, (void *)&scene->objects[j], j);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_plane && j < scene->nb_objects)
	{
		PRINT_DEBUG("Plane[%d] : %p (object %d)\n", i,  (void *)&scene->objects[j], j);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_cylinder && j < scene->nb_objects)
	{
		PRINT_DEBUG("Cylinder[%d] : %p (object %d)\n", i, (void *)&scene->objects[j], j);
		i++;
		j++;
	}
	PRINT_DEBUG("\n");
}

void	debug_print_inter_list(t_inter_list *list)
{
	int	i;

	i = 0;
	PRINT_DEBUG("Inter Count %d\n", list->count);
	while (i < list->count)
	{
		PRINT_DEBUG("Inter obj [%d] : %p\n", i, (void *)list->inters[i].obj);
		PRINT_DEBUG("Inter  [%d] : %.3f\n", i, list->inters[i].t);
		i++;
	}
}

void	debug_print_matrice(t_matrix m, char *matrix_type)
{
	int	i;
	int	j;

	i = 0;
	PRINT_DEBUG("Print %s matrix :\n\n", matrix_type);
	while (i < m.row)
	{
		j = 0;
		PRINT_DEBUG("|");
		while (j < m.col)
		{
			PRINT_DEBUG(" %.3f |", m.matrix[i][j]);
			if (m.matrix[i][j] < 10.0 && m.matrix[i][j] >= 0.0)
				PRINT_DEBUG(" ");
			j++;
		}
		PRINT_DEBUG("\n");
		i++;
	}
	PRINT_DEBUG("\n");
}
