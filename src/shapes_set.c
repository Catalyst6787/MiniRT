#include "minirt.h"

int	parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor)
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
	sphere->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	color.r = ato_buffer(&scene->buffer[i], &i, ',');
	color.g = ato_buffer(&scene->buffer[i], &i, ',');
	color.b = ato_buffer(&scene->buffer[i], &i, '\n');
	sphere->pos = &pos;
	sphere->color = &color;

	*cursor = i;
	return (1);
	//check
}

int	parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor)
{
	int	i;
	(void)minirt;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	color;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	color.r = ato_buffer(&scene->buffer[i], &i, ',');
	color.g = ato_buffer(&scene->buffer[i], &i, ',');
	color.b = ato_buffer(&scene->buffer[i], &i, '\n');
	plane->pos = &pos;
	plane->dir = &dir;
	plane->color = &color;
	*cursor = i;
	return (1);
	//check
}

int	parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor)
{
	int	i;
	(void)minirt;
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	color;

	i = *cursor + 1;
	while (!ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->height = ato_buffer(&scene->buffer[i], &i, ' ');
	color.r = ato_buffer(&scene->buffer[i], &i, ',');
	color.g = ato_buffer(&scene->buffer[i], &i, ',');
	color.b = ato_buffer(&scene->buffer[i], &i, '\n');
	cylinder->pos = &pos;
	cylinder->dir = &dir;
	cylinder->color = &color;
	*cursor = i;
	return (1);
	//check
}
