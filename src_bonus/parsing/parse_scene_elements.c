#include "minirt.h"

static void	parse_buffer(t_minirt *minirt,
						t_scene *scene,
						int *cursor,
						t_parsing_helper *s)
{
	int	i;

	i = *cursor;
	if (scene->buffer[i] == 'A')
		parse_ambiant_light(minirt, scene, &i);
	if (scene->buffer[i] == 'C')
		parse_camera(minirt, scene, &i);
	if (scene->buffer[i] == 'L')
		s->l += parse_light(minirt, scene, scene->lights[s->l], &i);
	if (scene->buffer[i] == 's')
		if (scene->buffer[++i] == 'p')
			s->s += parse_sphere(minirt, scene, scene->spheres[s->s], &i);
	if (scene->buffer[i] == 'p')
		if (scene->buffer[++i] == 'l')
			s->p += parse_plane(minirt, scene, scene->planes[s->p], &i);
	if (scene->buffer[i] == 'c')
	{
		if (scene->buffer[++i] == 'y')
			s->cy += parse_cylinder(minirt, scene, scene->cylinders[s->cy], &i);
		else if (scene->buffer[i] == 'o')
			s->co += parse_cone(minirt, scene, scene->cones[s->co], &i);
	}
	*cursor = i;
}

void	parse_scene_elements(t_minirt *minirt, t_scene *scene)
{
	int					cursor;
	t_parsing_helper	shape;

	shape.l = 0;
	shape.s = 0;
	shape.cy = 0;
	shape.co = 0;
	shape.p = 0;
	cursor = 0;
	while (scene->buffer[cursor])
	{
		while (scene->buffer[cursor]
			&& ft_isspace(scene->buffer[cursor]))
			cursor++;
		parse_buffer(minirt, minirt->scene, &cursor, &shape);
	}
}
