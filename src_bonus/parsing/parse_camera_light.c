#include "errors.h"
#include "libft.h"
#include "matrice.h"
#include "minirt.h"
#include "object.h"
#include "scene.h"
#include "vec3.h"

int	count_comas(char *buffer, int i)
{
	int	count;

	count = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	count_spaces_in_line(char *buffer, int i)
{
	int	count;

	count = 0;
	while (buffer [i] && !ft_isspace(buffer[i]))
		i++;
	while (buffer [i] && ft_isspace(buffer[i]))
		i++;
	while (buffer[i] && buffer[i] != '\n')
	{
		while (buffer[i] && !ft_isspace(buffer[i]))
			i++;
		if (buffer[i] == '\t' || buffer[i] == ' ')
		{
			while (buffer[i] && ft_isspace(buffer[i]))
				i++;
			count++;
		}
		if (!buffer[i] || buffer[i] == '\n')
			break ;
		i++;
	}
	if (buffer[i] == '\n' && ft_isspace(buffer[i - 1]))
		count--;
	return (count);
}

int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 2
		|| count_spaces_in_line(scene->buffer, i) != 1)
	{
		printf("d = %d\n", count_spaces_in_line(scene->buffer, i));
		quit(minirt, WRONG_AMB_DATA);
	}
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->ambient->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->ambient->color.w = 0;
	*cursor = i;
	return (1);
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4
		|| count_spaces_in_line(scene->buffer, i) != 2)
		quit(minirt, WRONG_CAM_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i])
		&& scene->buffer[i] != '-')
		i++;
	scene->camera->view.from.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.from.w = 1;
	scene->camera->view.to.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.to.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.to.z = ato_buffer(&scene->buffer[i], &i, ' ');
	check_direction_vector(minirt, &scene->camera->view.to);
	scene->camera->view.to.w = 1;
	scene->camera->view.up = get_vec3(0, 1, 0);
	scene->camera->hsize = WIN_W;
	scene->camera->vsize = WIN_H;
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n')
		* M_PI / 180;
	*cursor = i;
	return (1);
}

int	parse_light(t_minirt *minirt, t_scene *scene, t_light *light, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4
		|| count_spaces_in_line(scene->buffer, i) != 2)
		quit(minirt, WRONG_LIGHT_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i])
		&& scene->buffer[i] != '-')
		i++;
	light->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	light->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	light->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	light->pos.w = 1;
	light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	light->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	light->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	light->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	light->color.w = 0;
	*cursor = i;
	return (1);
}

int	set_obj_type(t_object *obj, int *cursor, char *buffer)
{
	if (!buffer || !buffer[0] || buffer[*cursor])
		return(1);
	if (!ft_strncmp(buffer + *cursor, "sp", 2))
		obj->type = SPHERE;
	else if (!ft_strncmp(buffer + *cursor, "cy", 2))
		obj->type = CYLINDER;
	else if (!ft_strncmp(buffer + *cursor, "pl", 2))
		obj->type = PLANE;
	else if (!ft_strncmp(buffer + *cursor, "co", 2))
		obj->type = CONE;
	return(0);
}

int parse_object(t_minirt *minirt, t_object *obj, int *cursor)
{
	int	i;
	t_shear	shear;
	
	i = *cursor;
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	if (set_obj_type(obj, cursor, minirt->scene->buffer))
		return(quit(minirt, WRONG_OBJ));
	obj->translation = get_translation_matrix(ato_vec3(minirt->scene->buffer, &i));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->rotation = get_rotation_matrix(ato_vec3(minirt->scene->buffer, &i));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->rotation = get_scaling_matrix(ato_vec3(minirt->scene->buffer, &i));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->material = get_default_material(ato_vec3(minirt->scene->buffer, &i), minirt->scene);
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->material.diffuse = ato_buffer(minirt->scene->buffer, &i, ' ');
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->material.specular = ato_buffer(minirt->scene->buffer, &i, ' ');
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->material.shininess = ato_buffer(minirt->scene->buffer, &i, ' ');
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->material.reflective = ato_buffer(minirt->scene->buffer, &i, ' ');
	// add more material here 
	obj->shearing = get_matrix(4, 4, 1);
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	if (minirt->scene->buffer[i] != '\n')
	{
		shear.xy = ato_buffer(minirt->scene->buffer, &i, ',');
		shear.xz = ato_buffer(minirt->scene->buffer, &i, ',');
		shear.yx= ato_buffer(minirt->scene->buffer, &i, ',');
		shear.yz= ato_buffer(minirt->scene->buffer, &i, ',');
		shear.zx= ato_buffer(minirt->scene->buffer, &i, ',');
		shear.zy= ato_buffer(minirt->scene->buffer, &i, '\n');
		obj->shearing = get_shearing_matrix(shear);
	}
	obj->transform = get_transformation(obj->translation, obj->rotation, obj->shearing, obj->scaling);
	return (0);
}
