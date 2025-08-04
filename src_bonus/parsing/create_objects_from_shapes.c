#include "minirt.h"

void	create_object_from_sphere(t_object *obj, t_sphere *s, int id)
{
	obj->type = SPHERE;
	obj->translation = get_translation_matrix(s->pos);
	obj->rotation = get_matrix(4, 4, 1);
	obj->shearing = get_matrix(4, 4, 1);
	obj->scaling = get_scaling_matrix(get_vec3(s->radius, s->radius, s->radius));;
	obj->transform = get_object_transformation(obj);
	obj->inv = get_inversed_matrix(obj->transform);
	obj->material = s->material;
	obj->id = id;
}

void	create_object_from_plane(t_object *obj, t_plane *pl, int id)
{
	obj->type = PLANE;
	obj->dir = pl->dir;
	obj->translation = get_translation_matrix(pl->pos);
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(obj->dir));
	obj->shearing = get_matrix(4, 4, 1);
	obj->scaling = get_matrix(4, 4, 1);
	obj->transform = get_object_transformation(obj);
	obj->inv = get_inversed_matrix(obj->transform);
	obj->material = pl->material;
	obj->obj_data.plane_normal = vec3_normalise(vec3_matrix_multiply(
				obj->transform,
				get_vec3(0, 1, 0)));
	obj->id = id;
}

void	create_object_from_cylinder(t_object *obj,
									t_cylinder *cy,
									int id)
{
	obj->type = CYLINDER;
	obj->dir = get_vec3(cy->dir.x, cy->dir.y, cy->dir.z);
	obj->translation = get_translation_matrix(cy->pos);
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(obj->dir));
	obj->shearing = get_matrix(4, 4, 1);
	obj->scaling = get_scaling_matrix(get_vec3(cy->radius, cy->height, cy->radius));
	obj->transform = get_object_transformation(obj);
	obj->inv = get_inversed_matrix(obj->transform);
	obj->material = cy->material;
	obj->obj_data.cylinder.max = cy->height / 2;
	obj->obj_data.cylinder.min = -(cy->height) / 2;
	obj->obj_data.cylinder.isclosed = 1;
	obj->id = id;
}

void	create_object_from_cone(t_object *obj,
									t_cone *co,
									int id)
{
	obj->type = CONE;
	obj->dir = co->dir;
	obj->translation = get_translation_matrix(co->pos);
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(obj->dir));
	obj->shearing = get_matrix(4, 4, 1);
	obj->scaling = get_scaling_matrix(get_vec3(co->radius, co->height, co->radius));
	obj->material = co->material;
	obj->transform = get_object_transformation(obj);
	obj->inv = get_inversed_matrix(obj->transform);
	obj->obj_data.cylinder.max = co->height / 2;
	obj->obj_data.cylinder.min = -(co->height) / 2;
	obj->obj_data.cylinder.isclosed = 1;
	obj->id = id;
}

void	create_object_array(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < scene->nb_sphere && j < scene->nb_objects)
	{
		create_object_from_sphere(&scene->objects[j], scene->spheres[i], i);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_plane && j < scene->nb_objects)
	{
		create_object_from_plane(&scene->objects[j], scene->planes[i], i);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_cylinder && j < scene->nb_objects)
	{
		create_object_from_cylinder(&scene->objects[j], scene->cylinders[i], i);
		i++;
		j++;
	}
	i = 0;
	while (i < scene->nb_cone && j < scene->nb_objects)
	{
		create_object_from_cone(&scene->objects[j], scene->cones[i], i);
		i++;
		j++;
	}
}
