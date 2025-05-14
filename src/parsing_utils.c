#include "minirt.h"

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

double	ato_buffer(char *ptr, int *cursor, int delim)
{
	int		i;
	double	n;

	i = *cursor;
	n = ft_atof(ptr);
	move_cursor(ptr, &i, delim);
	*cursor = i;
	return (n);
}
