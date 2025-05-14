
#include "minirt.h"

int	is_ok_color(t_vec3 *v)
{
	if (v->r < 0 || 255 < v->r)
		return (0);
	if (v->g < 0 || 255 < v->g)
		return (0);
	if (v->b < 0 || 255 < v->b)
		return (0);
	return (1);
}

int	is_ok_dir(t_vec3 *v)
{
	if (v->x < -1 || 1 < v->x)
		return (0);
	if (v->y < -1 || 1 < v->y)
		return (0);
	if (v->z < -1 || 1 < v->z)
		return (0);
	return (1);
}

int	is_ok_ratio(double var)
{
	if (var < 0 || 1 < var)
		return (0);
	return (1);
}

void	check_data_validity(t_minirt *minirt, t_scene *scene)
{
	int	i;

	i = -1;
	if (!is_ok_ratio(scene->ambient->brightness)
		|| !is_ok_color(scene->ambient->color))
		quit(minirt, WRONG_AMB_DATA);;
	if (scene->camera->fov < 0 || 180 < scene->camera->fov
		|| !is_ok_dir(scene->camera->dir))
		quit(minirt, WRONG_CAM_DATA);
	if (!is_ok_ratio(scene->light->brightness)
		|| !is_ok_color(scene->light->color))
		quit(minirt, WRONG_LIGHT_DATA);
	while (++i < scene->nb_sphere)
		if (!is_ok_color(scene->spheres[i]->color))
		{
			printf("r [%f] g[%f] b[%f]\n", scene->spheres[i]->color->r, scene->spheres[i]->color->g, scene->spheres[i]->color->b);
			quit(minirt, WRONG_SPH_DATA);
		}
	i = -1;
	while (++i < scene->nb_plane)
		if (!is_ok_dir(scene->planes[i]->dir)
			|| !is_ok_color(scene->planes[i]->color))
			quit(minirt, WRONG_PLAN_DATA);
	i = -1;
	while (++i < scene->nb_cylinder)
		if (!is_ok_dir(scene->cylinders[i]->dir)
			|| !is_ok_color(scene->cylinders[i]->color))
			quit(minirt, WRONG_CYL_DATA);
	/* check if data if valid (for example a color value of 300 is not valid) */
}

void	char_error_check(t_minirt *minirt,
							char c,
							const char *alpha_set,
							const char *sign_set)
{
	if (ft_isalpha(c)
		&& !ft_is_char_in_string(alpha_set, c))
	{
		quit(minirt, CHAR_ERR);
	}
	else if (!ft_isalpha(c)
		&& !ft_is_char_in_string(sign_set, c)
		&& !ft_isdigit(c))
	{
		quit(minirt, CHAR_ERR);
	}
}

void	check_each_lines(t_minirt *minirt, char *buffer)
{
	int		i;
	char	c;

	i = 0;
	while (ft_isspace(buffer[i]))
		i++;
	c = buffer[i++];
	while (buffer[i])
	{
		if (buffer[i] == c)
		{
			quit(minirt, CHAR_DOUBLE);
		}
		if (buffer[i] == '\n' && !ft_isspace(buffer[i]) && !ft_isspace(buffer[i + 1]))
		{
			while (buffer[i] || ft_isspace(buffer[i]))
				i++;
			c = buffer[i++];
		}
		i++;
	}
}

void	check_object_format(t_minirt *minirt, char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
	{
		if ((buffer[i] == 's' && buffer[i + 1] != 'p')
			|| (buffer[i] == 'p' && buffer[i + 1] != 'l')
			|| (buffer[i] == 'c' && buffer[i + 1] != 'y')
			|| ((buffer[i] == 'C' || buffer[i] == 'L'
			|| buffer[i] == 'A')  && buffer[i + 1] != ' '))
			quit(minirt, CHAR_ERR);
	}
}

void	check_characters_validity(t_minirt *minirt)
{
	const char	alpha_set[] = "ACLsplcy";
	const char	sign_set[] = " \n	.,-+";
	int	i;

	i = -1;
	while (minirt->scene->buffer[++i])
	{
		if (minirt->scene->buffer[i] == '\n')
		{
			while (minirt->scene->buffer[i] && ft_isspace(minirt->scene->buffer[i]))
				i++;
			if (minirt->scene->buffer[i])
				if (!ft_is_char_in_string(alpha_set, minirt->scene->buffer[i]))
					quit(minirt, SCENE_WRONG_CHAR_ERR);
		}
		if (!minirt->scene->buffer[i])
			break ;
		char_error_check(minirt, minirt->scene->buffer[i], alpha_set, sign_set);
		/* check if too much letter contained in alpha set (for example 3 p and only two l/s)*/
	}
	/* check for coments (#) */
	check_each_lines(minirt, minirt->scene->buffer);
	/* at this point, check with wrong arguments (ie ps instead of sp) */
}

