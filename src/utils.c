
#include "minirt.h"

void	swap_doubles(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = minirt->mlx->img_st->addr + (y * minirt->mlx->line_length + x
				* (minirt->mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		quit(minirt, PIXEL_PUT_ERR);
}

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
}

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
