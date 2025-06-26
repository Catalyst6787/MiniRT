
#include "minirt.h"

void	count_elements(t_scene *scene)
{
	int	i;

	i = -1;
	while (scene->buffer[++i])
	{
		if (scene->buffer[i] == 'A')
			scene->nb_amb++;
		else if (scene->buffer[i] == 'C')
			scene->nb_cam++;
		else if (scene->buffer[i] == 'L')
			scene->nb_light++;
		else if (scene->buffer[i] == 's' && scene->buffer[++i] == 'p')
			scene->nb_sphere++;
		else if (scene->buffer[i] == 'p' && scene->buffer[++i] == 'l')
			scene->nb_plane++;
		else if (scene->buffer[i] == 'c' && scene->buffer[++i] == 'y')
			scene->nb_cylinder++;
	}
	scene->nb_objects = scene->nb_sphere + scene->nb_plane + scene->nb_cylinder; // add here the next objects
}

void	parse_objects(t_scene *scene)
{
	int	cursor;
	int	s;
	int	c;
	int p;

	s = 0;
	c = 0;
	p = 0;
	cursor = 0;
	while (scene->buffer[cursor])
	{
		while (scene->buffer[cursor]
				&& ft_isspace(scene->buffer[cursor]))
			cursor++;
		if (scene->buffer[cursor] == 'A')
			parse_ambiant_light(scene, &cursor);
		if (scene->buffer[cursor] == 'C')
			parse_camera(scene, &cursor);
		if (scene->buffer[cursor] == 'L')
			parse_light(scene, &cursor);
		if (scene->buffer[cursor] == 's')
			if (scene->buffer[++cursor] == 'p')
				s += parse_sphere(scene, scene->spheres[s], &cursor);
		if (scene->buffer[cursor] == 'p')
			if (scene->buffer[++cursor] == 'l')
				p += parse_plane(scene, scene->planes[p], &cursor);
		if (scene->buffer[cursor] == 'c')
			if (scene->buffer[++cursor] == 'y')
				c += parse_cylinder(scene, scene->cylinders[c], &cursor);
	}
	/* should work if buffer_data checks correctly done*/
}


int	get_file_contents(int fd, char **file_contents)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	tmp = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		if (*file_contents)
			tmp = *file_contents;
		*file_contents = ft_strjoin(*file_contents, buf);
		if (tmp)
			free(tmp);
		tmp = NULL;
		free(buf);
		buf = get_next_line(fd);
	}
	if (!*file_contents)
		return (1);
	return (0);
}

void	set_scene_buffer(t_minirt *minirt, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		quit(minirt, FILE_OPEN_ERR);
	get_file_contents(fd, &minirt->scene->buffer);
	if (close(fd) == -1)
		quit(minirt, CLOSING_FILE_ERR);
	if (!minirt->scene->buffer)
		quit(minirt, EMPTY_FILE);
}

void	parse_scene(t_minirt *minirt, char *file_path)
{
	PRINT_DEBUG("\n%s\n\n", file_path);
	minirt->scene->buffer = NULL;
	check_file_name(minirt, file_path);
	set_scene_buffer(minirt, file_path);
	check_file_not_empty(minirt);
	check_characters_validity(minirt);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_objects(minirt->scene);
	set_objects_transformation(minirt->scene);
	set_objects_material(minirt->scene);
	check_data_validity(minirt, minirt->scene);
	create_object_list(minirt->scene);
	debug_print_scene_data(minirt);
	print_scene_ok_message();
	free(minirt->scene->buffer);
	minirt->scene->buffer = NULL;
	fill_intersection_table(minirt, minirt->render);
}
