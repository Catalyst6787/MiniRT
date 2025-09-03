/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:51:53 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 22:51:54 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "minirt.h"
#include "object.h"
#include "vec3.h"

void	get_transform_vec(t_minirt *minirt, t_object *obj,
			t_vec3 transformations[4], int *i)
{
	transformations[translation] = ato_vec3(minirt->scene->buffer, i, minirt);
	transformations[direction] = ato_vec3(minirt->scene->buffer, i, minirt);
	transformations[scaling] = ato_vec3(minirt->scene->buffer, i, minirt);
	transformations[color] = ato_vec3(minirt->scene->buffer, i, minirt);
	obj->material = get_default_material(
			vec3_double_division(transformations[color], 255), minirt->scene);
	obj->material.ambient = minirt->scene->ambient->brightness;
	obj->material.ambient_color = minirt->scene->ambient->color;
	obj->material.diffuse = ato_buffer(minirt->scene->buffer + *i, i, ' ');
	obj->material.specular = ato_buffer(minirt->scene->buffer + *i, i, ' ');
	obj->material.shininess = ato_buffer(minirt->scene->buffer + *i, i, ' ');
}

void	get_shearing(t_minirt *minirt, t_object *obj, int *i)
{
	t_shear shear;

	if (is_shearing(minirt->scene->buffer + *i))
	{
		obj->material.reflective
			= ato_buffer(minirt->scene->buffer + *i, i, ' ');
		shear.xy = ato_buffer(minirt->scene->buffer + *i, i, ',');
		shear.xz = ato_buffer(minirt->scene->buffer + *i, i, ',');
		shear.yx = ato_buffer(minirt->scene->buffer + *i, i, ',');
		shear.yz = ato_buffer(minirt->scene->buffer + *i, i, ',');
		shear.zx = ato_buffer(minirt->scene->buffer + *i, i, ',');
		shear.zy = ato_buffer(minirt->scene->buffer + *i, i, '\n');
		obj->shearing = get_shearing_matrix(shear);
	}
	else
	{
		obj->material.reflective
			= ato_buffer(minirt->scene->buffer + *i, i, '\n');
		obj->shearing = get_matrix(4, 4, 1);
	}
}

int	check_parsed_data(t_minirt *minirt, t_vec3 transformations[4], t_object *obj, int *cursor)
{
	if (check_transformation_data(transformations))
		return (print_until(minirt->scene->buffer + *cursor, '\n'),
			quit(minirt, TRANSFORMATION_PARSER_ERROR));
	if (double_isequal(0, get_determinant(obj->shearing)))
		return (print_until(minirt->scene->buffer + *cursor, '\n'),
			quit(minirt, PARSER_WRONG_SHEARING));
	if (check_material_data(obj->material))
		return (print_until(minirt->scene->buffer + *cursor, '\n'),
			quit(minirt, PARSER_WRONG_MATERIAL));
	return (0);
}

int	set_object_parameters(t_minirt *minirt, t_object *obj, t_vec3 transformations[4])
{
	obj->translation = get_translation_matrix(transformations[translation]);
	obj->dir = transformations[direction];
	obj->rotation = get_rotation_matrix(
			convert_dir_to_euler(vec3_normalise(transformations[direction])));
	obj->scaling = get_scaling_matrix(transformations[scaling]);
	obj->transform = get_object_transformation(obj);
	if (double_isequal(get_determinant(obj->transform), 0))
		quit(minirt, PARSER_NON_INVERTIBLE_MATRIX);
	obj->inv = get_inversed_matrix(obj->transform);
	if (obj->type == PLANE)
	{
		obj->obj_data.plane_normal = vec3_normalise(
				vec3_matrix_multiply(obj->transform, get_vec3(0, 1, 0)));
	}
	else if (obj->type == CYLINDER || obj->type == CONE)
	{
		obj->obj_data.cylinder.isclosed = true;
		obj->obj_data.cylinder.max = transformations[scaling].x / 2;
		obj->obj_data.cylinder.min = -(transformations[scaling].x) / 2;
	}
	return (0);
}

int	parse_object(t_minirt *minirt, t_object *obj, int *cursor)
{
	int		i;
	t_vec3	transformations[4];

	i = *cursor;
	if (!obj)
		quit(minirt, "error in parse object, obj doesnt exist");
	if (!is_valid_object(minirt->scene->buffer + *cursor))
		quit(minirt, "error in parse_object, object malformed");
	if (set_obj_type(obj, &i, minirt->scene->buffer))
		return (printf("unrecognized obj: [%s]",
				minirt->scene->buffer + *cursor), quit(minirt, WRONG_OBJ));
	while (ft_isspace(minirt->scene->buffer[i]))
		i++;
	get_transform_vec(minirt, obj, transformations, &i);
	get_shearing(minirt, obj, &i);
	check_parsed_data(minirt, transformations, obj, cursor);
	set_object_parameters(minirt, obj, transformations);
	*cursor = i;
	return (0);
}
