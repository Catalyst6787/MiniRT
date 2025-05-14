
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
		else if (scene->buffer[i] == 's')
		{
			if (scene->buffer[++i] == 'p')
				scene->nb_sphere++;
		}
		else if (scene->buffer[i] == 'p' && scene->buffer[i + 1] == 'l')
			scene->nb_plane++;
		else if (scene->buffer[i] == 'c' && scene->buffer[i + 1] == 'y')
			scene->nb_cylinder++;
	}
	/* warning but not error if not enough elements*/
}

void	parse_data(t_minirt *minirt, t_scene *scene)  /* at this point all file-format errors must have been checked*/
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

void	set_scene_buffer(t_minirt *minirt, char *file_path)
{
	char	buffer[BS];
	int		fd;
	int		file_len;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		quit(minirt, FILE_OPEN_ERR);
	file_len = read(fd, buffer, BS);
	close_fd_check(minirt, fd);
	if (file_len == -1)
		quit(minirt, READ_ERR);
	minirt->scene->buffer = malloc(sizeof(char) * (file_len + 1));
	if (!minirt->scene->buffer)
		quit(minirt, MALLOC_ERR);
	ft_strlcpy(minirt->scene->buffer, buffer, file_len);
}

void	alloc_elements(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	scene->ambient = malloc(sizeof(t_ambient));
	scene->light = malloc(sizeof(t_light));
	scene->camera = malloc(sizeof(t_camera));
	scene->spheres = malloc(sizeof(t_sphere *) * (scene->nb_sphere + 1));
	if (!scene->spheres && scene->nb_sphere)    // 2nd condition here to difference malloc error from no element and tests
		quit(minirt, MALLOC_ERR);
	while (i < scene->nb_sphere)
		scene->spheres[++i] = malloc(sizeof(t_sphere));
	scene->spheres[i] = NULL;
	i = -1;

	scene->planes = malloc(sizeof(t_plane *) * (scene->nb_plane + 1));
	if (!scene->planes && scene->nb_plane)
		quit(minirt, MALLOC_ERR);
	while (i < scene->nb_plane)
		scene->planes[++i] = malloc(sizeof(t_plane));
	scene->planes[i] = NULL;
	i = -1;

	scene->cylinders = malloc(sizeof(t_cylinder *) * (scene->nb_cylinder + 1));
	if (!scene->cylinders && scene->nb_cylinder)
		quit(minirt, MALLOC_ERR);
	while (i < scene->nb_cylinder)
		scene->cylinders[++i] = malloc(sizeof(t_cylinder));
	scene->cylinders[i] = NULL;
}


void	parse_scene(t_minirt *minirt, char *file_path)
{
	check_file_name(minirt, file_path);
	set_scene_buffer(minirt, file_path);
	print_scene(minirt, 1);
	check_characters_validity(minirt);
	count_elements(minirt->scene);
	single_elements_check(minirt, minirt->scene);
	alloc_elements(minirt, minirt->scene);
	parse_data(minirt, minirt->scene); /* current 2 */
	check_data_validity(minirt);
	print_scene_ok_message();
	// fill_img_data(minirt);
	print_scene_data(minirt);
	free(minirt->scene->buffer);
}























// static int	choose_parser(char *line, t_scene *scene)
// {
// 	if (line[0] == '#')
// 		return (0);
// 	else if (!ft_strncmp(line, "A ", 2))
// 		return (parse_ambiant(line, scene));
// 	else if (!ft_strncmp(line, "C ", 2))
// 		return (parse_camera(line, scene));
// 	else if (!ft_strncmp(line, "L ", 2))
// 		return (parse_light(line, scene));
// 	else if (!ft_strncmp(line, "sp ", 3))
// 		return (parse_sphere(line, scene));
// 	else if (!ft_strncmp(line, "pl ", 3))
// 		return (parse_plane(line, scene));
// 	else if (!ft_strncmp(line, "cy ", 3))
// 		return (parse_cylinder(line, scene));
// 	else
// 		return (ft_printf("field: <%s> is malformed. usage: <id> <...>\n",
// 				line), 1);
// }

// static int	parse_fields(char **scene_arr, t_scene *scene)
// {
// 	int	i;

// 	i = 0;
// 	while (scene_arr[i])
// 	{
// 		if (choose_parser(scene_arr[i], scene))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	parse(char *file_path, t_scene *scene)
// {
// 	int		fd;
// 	int		err;
// 	char	*file_contents;
// 	char	**scene_arr;

// 	fd = 0;
// 	err = 0;
// 	file_contents = NULL;
// 	scene_arr = NULL;
// 	if (check_file(file_path, &fd))
// 		return (1);
// 	if (get_file_contents(fd, &file_contents))
// 		return (close(fd),
// 			ft_printf("Error\nFile: <%s> is empty\n", file_path), 1);
// 	scene_arr = ft_split(file_contents, '\n');
// 	if (!scene_arr || !scene_arr[0])
// 		return (close(fd), free(scene_arr), free(file_contents),
// 			ft_printf("Error\nFile: <%s> is empty\n", file_path), 1);
// 	err = parse_fields(scene_arr, scene);
// 	free_tab(scene_arr);
// 	free_and_null((void **)&scene_arr);
// 	close(fd);
// 	free(file_contents);
// 	return (err);
// }
