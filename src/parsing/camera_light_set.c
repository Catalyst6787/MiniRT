#include "minirt.h"

int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->ambient->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->ambient->color->b = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->ambient->color->g = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->camera->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->camera->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}

int	parse_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->light->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->light->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->light->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->light->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->light->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->light->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}
