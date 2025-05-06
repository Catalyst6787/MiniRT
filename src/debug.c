/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:24:54 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 16:06:34 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	debug_print_keycode(int keycode)
{
	ft_printf("keycode: %d\n", keycode);
	return (0);
}

void	debug_aff_image(t_mlx_data *mlx)
{
	int		x;
	int		y;
	double	red;
	double	green;
	double	blue;
	int		color;

	x = 0;
	y = 0;
	while (y < WIN_H)
	{
		while (x < WIN_W)
		{
			red = (double)x / (WIN_W - 1);
			green = (double)y / (WIN_H - 1);
			blue = 0.0;
			color = ((int)(red * 255) << 16) | ((int)(green * 255) << 8) | (int)(blue * 255);
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
}

// void	debug_aff_image(t_mlx_data *mlx)
// {
// 	my_mlx_pixel_put(mlx, 1919, 1079, 0xff2d0);
// 	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
// }
