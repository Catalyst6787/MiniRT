/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:11:25 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/13 17:28:38 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*################################ CHECKS ######################################*/






void	check_file_name(t_minirt *minirt, char *file_path)
{
	if (!is_char_in_string(file_path, '.'))
		exit_program(minirt, EXT_MISSING_ERR);
	/* check extension */
}

void	check_data_validity(t_minirt *minirt)
{
	(void)minirt;
	/* check if data if valid (for example a color value of 300 is not valid) */

}

static void	char_error_check(t_minirt *minirt,
							char c,
							const char *alpha_set,
							const char *sign_set)
{
	if (ft_isalpha(c)
		&& !is_char_in_string(alpha_set, c))
		exit_program(minirt, CHAR_ERR);
	else if (!ft_isalpha(c)
		&& !is_char_in_string(sign_set, c)
		&& !ft_isdigit(c))
		exit_program(minirt, CHAR_ERR);
}

void	single_elements_check(t_minirt *minirt, t_scene *scene)
{
	if (scene->amb_count == 0)
		exit_program(minirt, MISSING_AMB_ERR);
	else if (scene->amb_count > 1)
		exit_program(minirt, TOO_MUCH_AMB_ERR);
	else if (scene->cam_count == 0)
		exit_program(minirt, MISSING_CAM_ERR);
	else if (scene->cam_count > 1)
		exit_program(minirt, TOO_MUCH_CAM_ERR);
	else if (scene->light_count == 0)
		exit_program(minirt, MISSING_LIGHT_ERR);
	else if (scene->light_count > 1)
		exit_program(minirt, TOO_MUCH_LIGHT_ERR);
}


void	element_checks(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	while (scene->buffer[++i])
	{
		if (scene->buffer[i] == 'A')
			scene->amb_count++;
		else if (scene->buffer[i] == 'C')
			scene->cam_count++;
		else if (scene->buffer[i] == 'L')
			scene->light_count++;
		else if (scene->buffer[i] == 's')
		{
			if (scene->buffer[++i] == 'p')
				scene->sph_count++;
		}
		else if (scene->buffer[i] == 'p' && scene->buffer[i + 1] == 'l')
			scene->plan_count++;
		else if (scene->buffer[i] == 'c' && scene->buffer[i + 1] == 'y')
			scene->cyl_count++;
	}
	single_elements_check(minirt, scene);
	/* warning but not error if not enough elements*/
}

void	check_characters_validity(t_minirt *minirt)
{
	const char	alpha_set[] = "ACLsplcy";
	const char	sign_set[] = " \n	.,-+";
	char		*scene;
	int	i;

	scene = minirt->scene->buffer;
	i = -1;
	while (scene[++i])
	{
		if (scene[i] == '\n')
		{
			while (scene[i] && ft_isspace(scene[i]))
				i++;
			if (!is_char_in_string(alpha_set, scene[i]))
				exit_program(minirt, SCENE_WRONG_CHAR_ERR);
		}
		char_error_check(minirt, scene[i], alpha_set, sign_set);
		/* check if too much letter contained in alpha set (for example 3 p andonly two l/s)*/
	}
	/* at this point, check with wrong arguments (ie ps instead of sp) */
	/* also check if t*/
	element_checks(minirt, minirt->scene);
}

















/*############################################################################*/













/*####################### DATA PARSING ##########################################*/



double	ft_atof(char *str)
{
	double	right;
	double	result;
	int		i;
	int		len;

	result = ft_atoi(str);
	while (*str != '.')
		str++;
	str++;
	right = ft_atoi(str);
	len = ft_intlen((int)right);
	i = -1;
	while (++i < len)
		right *= 0.1;
	result += right;
	return (result);
}

void	move_cursor(char *str, int *cursor, char c)
{
	int	i;

	i = *cursor;
	while (*str && *str != c && ++i)
		str++;
	while (*str && *str == c && ++i)
		str++;
	*cursor = i;
}



double	ato_buffer(char *ptr, int *cursor, int delim, char type)
{
	int		i;
	double	n;

	i = *cursor;
	if (type == 'i')
		n = ft_atoi(ptr);
	else
		n = ft_atof(ptr);
	move_cursor(ptr, &i, delim);
	*cursor = i;
	return (n);
}


void	set_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->ambient->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->ambient->color->b = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->ambient->color->g = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	set_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->camera->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->camera->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->camera->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	set_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->light->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->light->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->light->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->light->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->light->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->light->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	set_sphere(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->spheres->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->spheres->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->spheres->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->spheres->diameter = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->spheres->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->spheres->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->spheres->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	set_plane(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->planes->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->planes->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->planes->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->planes->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->planes->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->planes->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->planes->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->planes->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->planes->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	set_cylinder(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;
	(void)minirt;

	i = *cursor + 1;
	while (!ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->cylinders->pos->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->cylinders->pos->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->cylinders->pos->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->cylinders->dir->x = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->cylinders->dir->y = ato_buffer(&scene->buffer[i], &i, ',', 'f');
	scene->cylinders->dir->z = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->cylinders->diameter = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->cylinders->height = ato_buffer(&scene->buffer[i], &i, ' ', 'f');
	scene->cylinders->color->r = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->cylinders->color->g = (int)ato_buffer(&scene->buffer[i], &i, ',', 'i');
	scene->cylinders->color->b = (int)ato_buffer(&scene->buffer[i], &i, '\n', 'i');
	*cursor = i;
	//check
}

void	parse_data(t_minirt *minirt)  /* at this point all errors must have been checked*/
{
	int	cursor;
	(void) minirt;

	cursor = 0;

	while (minirt->scene->buffer[cursor])
	{
		while (minirt->scene->buffer[cursor]
				&& ft_isspace(minirt->scene->buffer[cursor]))
			cursor++;
		if (minirt->scene->buffer[cursor] == 'A')
			set_ambiant_light(minirt, minirt->scene, &cursor);
		if (minirt->scene->buffer[cursor] == 'C')
			set_camera(minirt, minirt->scene, &cursor);
		if (minirt->scene->buffer[cursor] == 'L')
			set_light(minirt, minirt->scene, &cursor);
		if (minirt->scene->buffer[cursor] == 's')
			if (minirt->scene->buffer[++cursor] == 'p')
				set_sphere(minirt, minirt->scene, &cursor);
		if (minirt->scene->buffer[cursor] == 'p')
			if (minirt->scene->buffer[++cursor] == 'l')
				set_plane(minirt, minirt->scene, &cursor);
		if (minirt->scene->buffer[cursor] == 'c')
			if (minirt->scene->buffer[++cursor] == 'y')
				set_cylinder(minirt, minirt->scene, &cursor);
	}
	// print_scene_data(minirt);
	/* maybe add check in the set*/
	/* should work if buffer_data checks correctly done*/
}






/*############################################################################*/




void	set_scene_buffer(t_minirt *minirt, char *file_path)
{
	char	buffer[BUFFER_SIZE];
	int		fd;
	int		file_len;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_program(minirt, FILE_OPEN_ERR);
	file_len = read(fd, buffer, BUFFER_SIZE);
	close_fd_check(minirt, fd);
	if (file_len == -1)
		exit_program(minirt, READ_ERR);
	minirt->scene->buffer = malloc(sizeof(char) * (file_len + 1));
	if (!minirt->scene->buffer)
		exit_program(minirt, MALLOC_ERR);
	ft_strlcpy(minirt->scene->buffer, buffer, file_len);
}

void	parse_scene(t_minirt *minirt, char *file_path)
{
	check_file_name(minirt, file_path);
	set_scene_buffer(minirt, file_path);
	// print_scene(minirt, 1);
	check_characters_validity(minirt);
	parse_data(minirt); /* current 2 */
	free(minirt->scene->buffer);
	check_data_validity(minirt);
	print_scene_ok_message();
	// fill_img_data(minirt);
	print_scene_data(minirt);
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
