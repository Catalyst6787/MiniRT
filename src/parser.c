
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
		else if (scene->buffer[i] == 's' && scene->buffer[++i] == 'p') // add check if buffer[i+1] != 'p'
				scene->nb_sphere++;
		else if (scene->buffer[i] == 'p' && scene->buffer[++i] == 'l')
			scene->nb_plane++;
		else if (scene->buffer[i] == 'c' && scene->buffer[++i] == 'y')
			scene->nb_cylinder++;
	}
	/* warning but not error if not enough elements*/
}

void	parse_objects(t_minirt *minirt, t_scene *scene)  /* at this point all file-format errors must have been checked*/
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
			parse_ambiant_light(minirt, scene, &cursor);
		if (scene->buffer[cursor] == 'C')
			parse_camera(minirt, scene, &cursor);
		if (scene->buffer[cursor] == 'L')
			parse_light(minirt, scene, &cursor);
		if (scene->buffer[cursor] == 's')
			if (scene->buffer[++cursor] == 'p')
				s += parse_sphere(minirt, scene, scene->spheres[s], &cursor);
		if (scene->buffer[cursor] == 'p')
			if (scene->buffer[++cursor] == 'l')
				p += parse_plane(minirt, scene, scene->planes[p], &cursor);
		if (scene->buffer[cursor] == 'c')
			if (scene->buffer[++cursor] == 'y')
				c += parse_cylinder(minirt, scene, scene->cylinders[c], &cursor);
	}
	// print_scene_data(minirt);
	/* maybe add check in the set*/
	/* should work if buffer_data checks correctly done*/
}

void	close_fd_check(t_minirt *minirt, int fd)
{
	if (close(fd) == -1)
		quit(minirt, CLOSING_FILE_ERR);
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
}


void	alloc_elements(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	scene->ambient = malloc(sizeof(t_ambient) );
	scene->light = malloc(sizeof(t_light));
	scene->camera = malloc(sizeof(t_camera));
	scene->spheres = malloc(sizeof(t_sphere *) * (scene->nb_sphere + 1));
	if (!scene->spheres && scene->nb_sphere)    // 2nd condition here to difference malloc error from no element and tests
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_sphere)  // ADD MALLOC CHECKS
		scene->spheres[i] = malloc(sizeof(t_sphere));
	scene->spheres[i] = NULL;
	i = -1;
	scene->planes = malloc(sizeof(t_plane *) * (scene->nb_plane + 1));
	if (!scene->planes && scene->nb_plane)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_plane)
		scene->planes[i] = malloc(sizeof(t_plane));
	scene->planes[i] = NULL;
	i = -1;
	scene->cylinders = malloc(sizeof(t_cylinder *) * (scene->nb_cylinder + 1));
	if (!scene->cylinders && scene->nb_cylinder)
		quit(minirt, MALLOC_ERR);
	while (++i < scene->nb_cylinder)
		scene->cylinders[i] = malloc(sizeof(t_cylinder));
	scene->cylinders[i] = NULL;
}

void	initialize_scene_ptr(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->planes = NULL;
	scene->spheres = NULL;
	scene->cylinders = NULL;
}

void	parse_scene(t_minirt *minirt, char *file_path)
{
	initialize_scene_ptr(minirt->scene);
	check_file_name(minirt, file_path);
	set_scene_buffer(minirt, file_path);
	check_characters_validity(minirt);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_objects(minirt, minirt->scene);
	print_scene_data(minirt);
	check_data_validity(minirt, minirt->scene);
	print_scene_ok_message();
	free(minirt->scene->buffer);
	minirt->scene->buffer = NULL;
}

