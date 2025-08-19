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
	if (!buffer || !buffer[0] || !buffer[*cursor])
		return(1);
	if (!obj)
		return(1);
	else if (!ft_strncmp(buffer + *cursor, "sp", 2))
		obj->type = SPHERE;
	else if (!ft_strncmp(buffer + *cursor, "cy", 2))
		obj->type = CYLINDER;
	else if (!ft_strncmp(buffer + *cursor, "pl", 2))
		obj->type = PLANE;
	else if (!ft_strncmp(buffer + *cursor, "co", 2))
		obj->type = CONE;
	else
		return(1);
	(*cursor) += 2;
	return(0);
}

int parse_object(t_minirt *minirt, t_object *obj, int *cursor)
{
	int	i;
	t_shear	shear;
	t_vec3	scaling;
	
	i = *cursor;
	// printf("parsing obj. buffer:\n%s\n", minirt->scene->buffer + i);
	if (!obj)
		return(quit(minirt, "error in parse object, obj doesnt exist"));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	if (set_obj_type(obj, &i, minirt->scene->buffer))
		return(printf("unrecognized obj: [%s]", minirt->scene->buffer + *cursor), quit(minirt, WRONG_OBJ));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	// printf("parsing translation. buffer:\n%s\n", minirt->scene->buffer + i);
	obj->translation = get_translation_matrix(ato_vec3(minirt->scene->buffer, &i, minirt));
	// printf("parsing rotation. buffer:\n%s\n", minirt->scene->buffer + i);
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(ato_vec3(minirt->scene->buffer, &i, minirt)));
	// printf("parsing scaling. buffer:\n%s\n", minirt->scene->buffer + i);
	scaling = ato_vec3(minirt->scene->buffer, &i, minirt);
	obj->scaling = get_scaling_matrix(scaling);
	// printf("parsing color. buffer:\n%s\n", minirt->scene->buffer + i);
	obj->material = get_default_material(vec3_double_division(ato_vec3(minirt->scene->buffer, &i, minirt), 255), minirt->scene);
	obj->material.ambient = minirt->scene->ambient->brightness;
	obj->material.ambient_color = minirt->scene->ambient->color;
	// printf("parsing diffuse buffer:\n%s\n", minirt->scene->buffer + i);
	obj->material.diffuse = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	// printf("parsing specular buffer:\n%s\n", minirt->scene->buffer + i);
	obj->material.specular = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	// printf("parsing shininess buffer:\n%s\n", minirt->scene->buffer + i);
	obj->material.shininess = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	// printf("parsing reflective buffer:\n%s\n", minirt->scene->buffer + i);
	obj->material.reflective = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	obj->shearing = get_matrix(4, 4, 1);
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	if (minirt->scene->buffer[i] != '\n')
	{
		// printf("parsing shearing buffer:\n%s\n", minirt->scene->buffer + i);
		shear.xy = ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.xz = ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.yx= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.yz= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.zx= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.zy= ato_buffer(minirt->scene->buffer + i, &i, '\n');
		obj->shearing = get_shearing_matrix(shear);
	}
	obj->transform = get_transformation(obj->translation, obj->rotation, obj->shearing, obj->scaling);
	obj->inv = get_inversed_matrix(obj->transform);
	if (obj->type == PLANE)
	{
		obj->obj_data.plane_normal = vec3_normalise(vec3_matrix_multiply(obj->transform, get_vec3(0, 1, 0)));
	}
	else if (obj->type == CYLINDER || obj->type == CONE) // TODO unhardcode
	{
		obj->obj_data.cylinder.isclosed = true;
		obj->obj_data.cylinder.max = scaling.x / 2;
		obj->obj_data.cylinder.min = -(scaling.x) / 2;
	}
	*cursor = i;
	return (0);
}
