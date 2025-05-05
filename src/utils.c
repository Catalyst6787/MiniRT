/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:44:30 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/05 16:51:38 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_st->addr + (y * mlx->line_length + x
			* (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	end_mlx_loop(t_mlx_data *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

int	debug_print_keycode(int keycode)
{
	ft_printf("keycode: %d\n", keycode);
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

int	quit(t_mlx_data *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_image(mlx->mlx, mlx->img_st->img);
	mlx->img_st->addr = NULL;
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
