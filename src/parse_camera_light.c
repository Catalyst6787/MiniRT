#include "minirt.h"

int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	scene->ambient->color = malloc(sizeof(t_vec3));
	if (!scene->ambient->color)
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->ambient->color->r = ato_buffer(&scene->buffer[i], &i, ',');
	scene->ambient->color->b = ato_buffer(&scene->buffer[i], &i, ',');
	scene->ambient->color->g = ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	scene->camera->dir =  malloc(sizeof(t_vec3));
	if (!scene->camera->dir)
		quit(minirt, MALLOC_ERR);
	scene->camera->pos =  malloc(sizeof(t_vec3));
	if (!scene->camera->pos)
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->camera->pos->x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->pos->y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->pos->z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->dir->x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->dir->y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->dir->z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}

int	parse_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	scene->light->pos = malloc(sizeof(t_vec3)); 
	if (!scene->light->pos)
		quit(minirt, MALLOC_ERR);
	scene->light->color = malloc(sizeof(t_vec3)); 
	if (!scene->light->color)
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->light->pos->x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos->y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos->z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->color->r = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->color->g = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->color->b = ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}
