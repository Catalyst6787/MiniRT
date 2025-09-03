#include "minirt.h"

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

int print_until(char *s, char c)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	if (s && s[i])
		return(write(1, s, i));
	return(0);
}

int	check_direction_validity(t_vec3 dir)
{
	if (double_isequal(dir.x, 0)
			&& double_isequal(dir.y, 0)
			&& double_isequal(dir.z, 0))
		return (1);
	return(0);
}

int	check_scaling_validity(t_vec3 scaling)
{
	if (double_isequal(scaling.x, 0)
			|| double_isequal(scaling.y, 0)
			|| double_isequal(scaling.z, 0))
		return (1);
	return(0);
}

int check_color_validity(t_vec3 color)
{
	if (color.r > 255 || color.r < 0)
		return (1);
	if (color.g > 255 || color.g < 0)
		return (1);
	if (color.b > 255 || color.b < 0)
		return (1);
	return (0);
}


int	check_transformation_data(t_vec3 transformations[4])
{
	if (check_direction_validity(transformations[direction]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_DIRECTION), direction);
	if (check_scaling_validity(transformations[scaling]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_SCALE), scaling);
	if (check_color_validity(transformations[color]))
		return (print_err(__FILE__, LINE, PARSER_WRONG_COLOR), color);
	return (0);
}

int check_material_data(t_material material)
{
	if (material.ambient > 1 || material.ambient < 0)
		return (1);
	if (check_color_validity(material.ambient_color))
		return (1);
	if (material.diffuse > 1 || material.diffuse < 0)
		return (1);
	if (material.specular > 1 || material.specular < 0)
		return (1);
	if (material.shininess > 500 || material.shininess < 1)
		return (1);
	if (material.reflective > 1 || material.reflective < 0)
		return (1);
	return (0);
}


int parse_object(t_minirt *minirt, t_object *obj, int *cursor)
{
	int	i;
	t_shear	shear;
	t_vec3	transformations[4];

	i = *cursor;
	if (!obj)
		quit(minirt, "error in parse object, obj doesnt exist");
	if (!is_valid_object(minirt->scene->buffer + *cursor))
		quit(minirt, "error in parse_object, object malformed");
	if (set_obj_type(obj, &i, minirt->scene->buffer))
		return(printf("unrecognized obj: [%s]", minirt->scene->buffer + *cursor), quit(minirt, WRONG_OBJ));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	transformations[translation] = ato_vec3(minirt->scene->buffer, &i, minirt);
	transformations[direction] = ato_vec3(minirt->scene->buffer, &i, minirt);
	transformations[scaling] = ato_vec3(minirt->scene->buffer, &i, minirt);
	transformations[color] = ato_vec3(minirt->scene->buffer, &i, minirt);
	obj->material = get_default_material(vec3_double_division(transformations[color], 255), minirt->scene);
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
	if (check_transformation_data(transformations))
		return(print_until(minirt->scene->buffer + *cursor, '\n'), quit(minirt, TRANSFORMATION_PARSER_ERROR));
	if (double_isequal(0, get_determinant(obj->shearing)))
		return(print_until(minirt->scene->buffer + *cursor, '\n'), quit(minirt, PARSER_WRONG_SHEARING));
	if (check_material_data(obj->material))
		return(print_until(minirt->scene->buffer + *cursor, '\n'), quit(minirt, PARSER_WRONG_MATERIAL));
	obj->translation = get_translation_matrix(transformations[translation]);
	obj->dir = transformations[direction]; //added for change_element_rotation
	obj->rotation = get_rotation_matrix(convert_dir_to_euler(vec3_normalise(transformations[direction])));
	obj->scaling = get_scaling_matrix(transformations[scaling]);
	obj->transform = get_object_transformation(obj);
	if (double_isequal(get_determinant(obj->transform), 0))
		quit(minirt, PARSER_NON_INVERTIBLE_MATRIX);
	obj->inv = get_inversed_matrix(obj->transform);
	if (obj->type == PLANE)
	{
		obj->obj_data.plane_normal = vec3_normalise(vec3_matrix_multiply(obj->transform, get_vec3(0, 1, 0)));
	}
	else if (obj->type == CYLINDER || obj->type == CONE) // TODO unhardcode
	{
		obj->obj_data.cylinder.isclosed = true;
		obj->obj_data.cylinder.max = transformations[scaling].x / 2;
		obj->obj_data.cylinder.min = -(transformations[scaling].x) / 2;
	}
	*cursor = i;
	return (0);
}
