/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:23:59 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/14 10:58:43 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	(void) mlx;
	mlx_loop_end(mlx->mlx);
	return (0);
}

int	handle_keypress(int keycode, t_mlx_data *mlx)
{
	if (keycode == Q || keycode == ESC)
		end_mlx_loop(mlx);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		ft_printf("WASD pressed\n");
	else if (keycode == SPACE)
		ft_printf("space pressed\n");
	else
		ft_printf("unknow action: %d\n", keycode);
	return (0);
}

int	handle_mouseclick(int button, int x, int y, t_mlx_data *mlx)
{
	(void)mlx;
	ft_printf("Mouseclick at: x=%d, y=%d, Button:%d\n", x, y, button);
	// my_mlx_pixel_put(mlx, x, y, 8029619);
	// mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
	return (0);
}
