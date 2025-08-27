#include "errors.h"
#include "ft_printf.h"
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

static int is_shearing(char *s)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != ' ' && s[i] != '\n')
		i++;
	while (s && s[i] && ft_isspace(s[i]))
		i++;
	if (ft_isdigit(s[i]))
		return(1);
	else
		return(0);
}

static int print_until(char *s, char c)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	if (s && s[i])
		return(write(1, s, i));
	return(0);
}

static int	is_valid_double(char *s, int *length)
{
	int i;

	i = 0;
	if (!s || !s[0])
		return(1);
	if (s[i] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != '.')
	{
		if ((s[i] == ' ' || s[i] == ',' || s[i] == '\n') && i < 18)
			return (*length += i, 1);
		else
			return (printf("invalid double, more than 17 significant digits: "), print_until(s, s[i]), 0);
	}
	i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (i < 18)
		return(*length += i, 1);
	return(printf("invalid double, more than 17 significant digits\n"), print_until(s, s[i]), 0);
}

static int	is_valid_vector(char *s, int *length)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (e < 3)
	{
		if (!is_valid_double(s + i, length))
			return (0);
		i += *length;
		*length = 0;
		if (e != 2 && s[i] != ',')
			return (0);
		if (e != 2)
			i++;
		e++;
	}
	return (*length = i, 1);
}

static int	is_valid_object(char *s)
{
	int	i;
	int	e;
	int	length;

	i = 0;
	e = 0;
	length = 0;
	while (s && s[i] && ft_isspace(s[i]))
		i++;
	if (!ft_isalpha(s[i]) || !ft_isalpha(s[i + 1]))
		return (0);
	i += 2;
	if (!ft_isspace(s[i]))
		return (0);
	i++;
	while (e < 4)
	{
		if (!is_valid_vector(s + i, &length))
			return (0);
		i += length;
		length = 0;
		if (!ft_isspace(s[i]))
			return (0);
		i++;
		e++;
	}
	e = 0;
	while (e < 4)
	{
		if (!is_valid_double(s + i, &length))
			return (0);
		i += length;
		length = 0;
		if (e != 3 && !ft_isspace(s[i]))
			return (0);
		if (e != 3)
			i++;
		e++;
	}
	e = 0;
	if (s[i] == '\n' || (s[i] == ' ' && s[i + 1] == '\n'))
		return(1);
	else if (!ft_isspace(s[i]))
		return (0);
	i++;
	while (e < 6)
	{
		if (!is_valid_double(s + i, &length))
			return (0);
		i += length;
		length = 0;
		if (e != 5 && s[i] != ',')
			return (0);
		if (e != 5)
			i++;
		e++;
	}
	if (s[i] == '\n' || (s[i] == ' ' && s[i + 1] == '\n'))
		return (1);
	return (0);
}

int parse_object(t_minirt *minirt, t_object *obj, int *cursor)
{
	int	i;
	t_shear	shear;
	t_vec3	scaling;

	i = *cursor;
	if (!obj)
		return(quit(minirt, "error in parse object, obj doesnt exist"));
	if (!is_valid_object(minirt->scene->buffer + *cursor))
		return(quit(minirt, "error in parse_object, object malformed"));
	if (set_obj_type(obj, &i, minirt->scene->buffer))
		return(printf("unrecognized obj: [%s]", minirt->scene->buffer + *cursor), quit(minirt, WRONG_OBJ));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	obj->translation = get_translation_matrix(ato_vec3(minirt->scene->buffer, &i, minirt));
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(vec3_normalise(ato_vec3(minirt->scene->buffer, &i, minirt))));
	scaling = ato_vec3(minirt->scene->buffer, &i, minirt);
	obj->scaling = get_scaling_matrix(scaling);
	obj->material = get_default_material(vec3_double_division(ato_vec3(minirt->scene->buffer, &i, minirt), 255), minirt->scene);
	obj->material.ambient = minirt->scene->ambient->brightness;
	obj->material.ambient_color = minirt->scene->ambient->color;
	obj->material.diffuse = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	obj->material.specular = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	obj->material.shininess = ato_buffer(minirt->scene->buffer + i, &i, ' ');
	if (is_shearing(minirt->scene->buffer + i))
	{
		obj->material.reflective = ato_buffer(minirt->scene->buffer + i, &i, ' ');
		shear.xy = ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.xz = ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.yx= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.yz= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.zx= ato_buffer(minirt->scene->buffer + i, &i, ',');
		shear.zy= ato_buffer(minirt->scene->buffer + i, &i, '\n');
		obj->shearing = get_shearing_matrix(shear);
	}
	else
	{
		obj->material.reflective = ato_buffer(minirt->scene->buffer + i, &i, '\n');
		obj->shearing = get_matrix(4, 4, 1);
	}
	obj->transform = get_object_transformation(obj);
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
