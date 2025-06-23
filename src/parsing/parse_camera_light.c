#include "minirt.h"

int	parse_ambiant_light(t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->ambient->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.b = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.g = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->ambient->color.w = 0;
	*cursor = i;
	return (1);
	//check
}

int	parse_camera(t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->camera->view.from.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.from.w = 1;
	scene->camera->view.from.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.from.w = 0;
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}

int	parse_light(t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->light->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->pos.w = 1;
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->light->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->light->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->light->color.w = 0;
	*cursor = i;
	return (1);
	//check
}
