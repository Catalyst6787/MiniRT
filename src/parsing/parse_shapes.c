#include "minirt.h"

int	parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor)
{
	int	i;

	sphere->pos = malloc(sizeof(t_vec3));
	sphere->color = malloc(sizeof(t_vec3));
	if (!sphere->pos || !sphere->color)
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	sphere->pos->x = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->pos->y = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->pos->z = ato_buffer(&scene->buffer[i], &i, ' ');
	sphere->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	sphere->color->r = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->color->g = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->color->b = ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}

int	parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor)
{
	int	i;

	plane->pos = malloc(sizeof(t_vec3));
	plane->dir = malloc(sizeof(t_vec3));
	plane->color = malloc(sizeof(t_vec3));
	if (!plane->pos || !plane->color || !plane->dir )
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	plane->pos->x = ato_buffer(&scene->buffer[i], &i, ',');
	plane->pos->y = ato_buffer(&scene->buffer[i], &i, ',');
	plane->pos->z = ato_buffer(&scene->buffer[i], &i, ' ');
	plane->dir->x = ato_buffer(&scene->buffer[i], &i, ',');
	plane->dir->y = ato_buffer(&scene->buffer[i], &i, ',');
	plane->dir->z = ato_buffer(&scene->buffer[i], &i, ' ');
	plane->color->r = ato_buffer(&scene->buffer[i], &i, ',');
	plane->color->g = ato_buffer(&scene->buffer[i], &i, ',');
	plane->color->b = ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}

int	parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor)
{
	int	i;

	cylinder->pos = malloc(sizeof(t_vec3));
	cylinder->dir = malloc(sizeof(t_vec3));
	cylinder->color = malloc(sizeof(t_vec3));
	if (!cylinder->pos || !cylinder->color || !cylinder->dir )
		quit(minirt, MALLOC_ERR);
	i = *cursor + 1;
	while (!ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	cylinder->pos->x = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->pos->y = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->pos->z = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->dir->x = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->dir->y = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->dir->z = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->height = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->color->r = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->color->g = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->color->b = ato_buffer(&scene->buffer[i], &i, '\n');
	*cursor = i;
	return (1);
	//check
}
