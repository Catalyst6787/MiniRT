#include "minirt.h"

int	parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	sphere->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	sphere->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	sphere->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	sphere->diameter = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	sphere->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	sphere->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	sphere->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}

int	parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	plane->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	plane->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	plane->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	plane->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	plane->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	plane->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	plane->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	plane->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	plane->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}

int	parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (!ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	cylinder->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	cylinder->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	cylinder->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	cylinder->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	cylinder->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	cylinder->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	cylinder->diameter = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	cylinder->height = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	cylinder->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	cylinder->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	cylinder->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	return (1);
	//check
}