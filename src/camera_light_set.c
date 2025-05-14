#include "minirt.h"

int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;
	t_vec3	color;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	color.r = ato_buffer(&scene->buffer[i], &i, ',');
	color.b = ato_buffer(&scene->buffer[i], &i, ',');
	color.g = ato_buffer(&scene->buffer[i], &i, '\n');
	scene->ambient->color = &color;
	*cursor = i;
	return (1);
	//check
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;
	t_vec3	*dir;
	t_vec3	pos;

	dir =  malloc(sizeof(t_vec3));
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	dir->x = ato_buffer(&scene->buffer[i], &i, ',');
	dir->y = ato_buffer(&scene->buffer[i], &i, ',');
	dir->z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n');
	scene->camera->pos = &pos;
	scene->camera->dir = dir;
	*cursor = i;
	return (1);
	//check
}

int	parse_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;
	t_vec3	pos;
	t_vec3	color;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	color.r = ato_buffer(&scene->buffer[i], &i, ',');
	color.g = ato_buffer(&scene->buffer[i], &i, ',');
	color.b = ato_buffer(&scene->buffer[i], &i, '\n');
	scene->light->pos = &pos;
	scene->light->color = &color;
	*cursor = i;
	return (1);
	//check
}
