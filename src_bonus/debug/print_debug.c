#include "debug.h"
#include "minirt.h"
#include "object.h"

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
	t_object obj;
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
	PRINT_DEBUG("	Ratio : %.4f\n", minirt->scene->ambient->brightness);
	PRINT_DEBUG("	r g b : %.4f %.4f %.4f\n\n", minirt->scene->ambient->color.r,minirt->scene->ambient->color.g, minirt->scene->ambient->color.b);
	PRINT_DEBUG("Camera :\n\n");
	PRINT_DEBUG("	pos : %.4f %.4f %.4f\n", minirt->scene->camera->view.from.x, minirt->scene->camera->view.from.y, minirt->scene->camera->view.from.z);
	PRINT_DEBUG("	dir : %.4f %.4f %.4f\n", minirt->scene->camera->view.to.x, minirt->scene->camera->view.to.y, minirt->scene->camera->view.to.z);
	PRINT_DEBUG("	FOV : %f\n\n", minirt->scene->camera->fov);
	while (++i < minirt->scene->nb_light)
	{
		PRINT_DEBUG("Light[%d/%d] :\n\n", i + 1, minirt->scene->nb_light);
		PRINT_DEBUG("	pos : %.4f %.4f %.4f\n", minirt->scene->lights[i]->pos.x, minirt->scene->lights[i]->pos.y, minirt->scene->lights[i]->pos.z);
		PRINT_DEBUG("	Ratio : %.4f\n", minirt->scene->lights[i]->brightness);
		PRINT_DEBUG("	r g b : %.4f %.4f %.4f\n\n", minirt->scene->lights[i]->color.r, minirt->scene->lights[i]->color.g, minirt->scene->lights[i]->color.b);
	}
	i = -1;
	while (++i < minirt->scene->nb_objects)
	{
		obj = minirt->scene->objects[i];
		PRINT_DEBUG("Object[%d/%d] :\n\n", i + 1, minirt->scene->nb_objects);
		PRINT_DEBUG("Type: ");
		if (obj.type == SPHERE)
			PRINT_DEBUG("Sphere");
		else if (obj.type == PLANE)
			PRINT_DEBUG("Plane");
		else if (obj.type == CYLINDER)
			PRINT_DEBUG("Cylinder");
		else if (obj.type == CONE)
			PRINT_DEBUG("Cone");
		PRINT_DEBUG("\n");
		// debug_print_vec(&obj.dir, "direction");
		PRINT_DEBUG("\n");
		debug_print_matrice(obj.translation, "translation");
		debug_print_matrice(obj.rotation, "rotation");
		debug_print_matrice(obj.scaling, "scaling");
		debug_print_matrice(obj.shearing, "shearing");
		debug_print_matrice(obj.transform, "transform");
		debug_print_matrice(obj.inv, "inverse transform");
		PRINT_DEBUG("\nMaterial:\n");
		debug_print_vec(&obj.material.color, "color");
		PRINT_DEBUG("\n");
		PRINT_DEBUG("ambiant brightness: %f\n", obj.material.ambient);
		debug_print_vec(&obj.material.ambient_color, "ambiant color");
		PRINT_DEBUG("\n");
		PRINT_DEBUG("diffuse: %f\n", obj.material.diffuse);
		PRINT_DEBUG("specular: %f\n", obj.material.specular);
		PRINT_DEBUG("shininess: %f\n", obj.material.shininess);
		PRINT_DEBUG("reflective: %f\n\n", obj.material.reflective);
	}
	PRINT_DEBUG("\n");
}

void	debug_print_objects_pointers(t_scene *scene)
{
	int	i;

	i = 0;
	PRINT_DEBUG("Objects pointers :\n\n");
	while (i < scene->nb_objects)
	{
		PRINT_DEBUG("Object[%d], ", i);
		if (scene->objects[i].type == SPHERE)
			PRINT_DEBUG("Sphere");
		if (scene->objects[i].type == PLANE)
			PRINT_DEBUG("Plane");
		if (scene->objects[i].type == CYLINDER)
			PRINT_DEBUG("Cylinder");
		if (scene->objects[i].type == CONE)
			PRINT_DEBUG("Cone");
		PRINT_DEBUG(", ptr=[%p]", (void*)&scene->objects[i]);
		PRINT_DEBUG("\n");
		i++;
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
