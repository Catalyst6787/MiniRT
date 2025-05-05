/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:00:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/05 15:52:48 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_mlx_data	mlx;
	t_img_data	img;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "miniRT");
	img.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	mlx.img_st = &img;
	mlx_hook(mlx.mlx_win, 2, 1L << 0, end_mlx_loop, &mlx);

	my_mlx_pixel_put(&mlx, 5, 5, 8029619);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img.img, 0, 0);

	mlx_loop(mlx.mlx);

	mlx_clear_window(mlx.mlx, mlx.mlx_win);
	mlx_destroy_image(mlx.mlx, mlx.img_st->img);
	mlx.img_st->addr = NULL;
	mlx_destroy_window(mlx.mlx, mlx.mlx_win);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
	return (0);
}
