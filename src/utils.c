
#include "minirt.h"


int	get_color_as_int(t_vec3 *color)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(color->r * 255.0);
	green = (int)(color->g * 255.0);
	blue = (int)(color->b * 255.0);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
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
	return ; // REMOVE FOR RAY TRACING CHALLENGE
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("file: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(", line: ", STDERR_FILENO);
	ft_putstr_fd(ft_itoa(line), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
}
