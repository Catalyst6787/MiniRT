#include "libft.h"
#include "minirt.h"
#include "vec3.h"

void	free_and_null(void	**ptr)
{
	free(*ptr);
	ptr = NULL;
}

void	print_err(char *file, int line, char *s)
{
	char	*line_str;

	line_str = ft_itoa(line);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("file: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(", line: ", STDERR_FILENO);
	ft_putstr_fd(line_str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	free(line_str);
}

int	get_max_int(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	get_min_int(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

// return a vector (w = 0), set w to 1 for a point
t_vec3	ato_vec3(char *s, int *cursor)
{
	t_vec3	v;

	while (ft_isspace(s[*cursor]))
		cursor++;
	v.x = ato_buffer(s, cursor, ',');
	v.y = ato_buffer(s, cursor, ',');
	v.z = ato_buffer(s, cursor, ',');
	v.w = 0;
	return(v);
}
