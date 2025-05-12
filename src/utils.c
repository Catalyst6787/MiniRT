/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:44:30 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 15:35:43 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = mlx->img_st->addr + (y * mlx->line_length + x
				* (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
	{
		ft_printf("Error! my_mlx_pixel_put: %s",
			"Tried to set pixel outside of window, quitting\n");
		quit(mlx);
	}
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
