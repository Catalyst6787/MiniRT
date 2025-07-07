#include "minirt.h"

int	parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4)
		quit(minirt, WRONG_SPH_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	sphere->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	sphere->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	sphere->pos.w = 1;
	sphere->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	sphere->radius = sphere->diameter / 2;
	sphere->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	sphere->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	sphere->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	*cursor = i;
	return (1);
	//check
}

int	parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 6)
		quit(minirt, WRONG_PLANE_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	plane->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	plane->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	plane->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	plane->pos.w = 1;
	plane->dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	plane->dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	plane->dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	plane->dir.w = 0;
	plane->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	plane->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	plane->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	*cursor = i;
	return (1);
	//check
}

int	parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 6)
		quit(minirt, WRONG_CYL_DATA);
	while (!ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	cylinder->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->pos.w = 1;
	cylinder->dir.x = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->dir.y = ato_buffer(&scene->buffer[i], &i, ',');
	cylinder->dir.z = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->dir.w = 0;
	cylinder->diameter = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->height = ato_buffer(&scene->buffer[i], &i, ' ');
	cylinder->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	cylinder->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	cylinder->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	*cursor = i;
	return (1);
	//check
}
