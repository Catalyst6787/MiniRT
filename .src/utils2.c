#include "minirt.h"

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
