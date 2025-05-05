/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:44:30 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/05 15:51:01 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_st->addr + (y * mlx->line_length + x
			* (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	end_mlx_loop(int keycode, t_mlx_data *mlx)
{
	(void)keycode;
	mlx_loop_end(mlx->mlx);
	// exit(0);
	return (0);
}
