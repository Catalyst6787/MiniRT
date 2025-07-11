#include "minirt.h"

void	objects_alloc(t_minirt *minirt, t_scene *scene)
{
	scene->objects = malloc(sizeof(t_object) * (scene->nb_objects + 1));
	if (!scene->objects && scene->nb_objects)
		quit(minirt, MALLOC_ERR);
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

char	*trim_ato_ptr(char *ptr, int delim)
{
	int		i;
	char	*dest;

	i = 0;
	if (delim == ' ')
		while (ptr[i] && ptr[i] != delim && ptr[i] != '\t')
			i++;
	else
		while (ptr[i] && ptr[i] != delim)
			i++;
	dest = ft_substr(ptr, 0, i);
	return (dest);
}

double	ato_buffer(char *ptr, int *cursor, int delim)
{
	int		i;
	double	n;
	char	*n_str;

	i = *cursor;
	n_str = trim_ato_ptr(ptr, delim);
	n = ft_atof(n_str);
	move_cursor(ptr, &i, delim);
	if (n_str)
		free(n_str);
	*cursor = i;
	return (n);
}
