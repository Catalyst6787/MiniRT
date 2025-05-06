/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:21:39 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 16:34:53 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_structure(t_mlx_data *mlx, t_img_data *img)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "miniRT");
	img->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(img->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx->img_st = img;
	return (0);
}

int	init_events(t_mlx_data *mlx)
{
	mlx_hook(mlx->mlx_win, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->mlx_win, 17, 1L << 0, end_mlx_loop, mlx);
	mlx_hook(mlx->mlx_win, 4, 1L << 2, handle_mouseclick, mlx);
	return (0);
}
