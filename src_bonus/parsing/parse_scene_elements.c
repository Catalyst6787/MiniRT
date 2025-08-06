#include "minirt.h"
#include "object.h"

static void	parse_buffer(t_minirt *minirt,
						t_scene *scene,
						int *cursor,
						t_object *obj)
{
	if (scene->buffer[*cursor] == 'A')
		parse_ambiant_light(minirt, scene, cursor);
	else if (scene->buffer[*cursor] == 'C')
		parse_camera(minirt, scene, cursor);
	else if (scene->buffer[*cursor] == 'L')
		parse_light(minirt, scene, minirt->scene->lights[minirt->scene->nb_light], cursor);
	else
		parse_object(minirt, obj, cursor);
}

void	parse_scene_elements(t_minirt *minirt, t_scene *scene)
{
	int					cursor;
	int					nb_obj;

	cursor = 0;
	nb_obj = 0;
	while (scene->buffer[cursor])
	{
		while (scene->buffer[cursor]
			&& ft_isspace(scene->buffer[cursor]))
			cursor++;
		parse_buffer(minirt, minirt->scene, &cursor, &minirt->scene->objects[nb_obj]);
		nb_obj++;
	}
}
