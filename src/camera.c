/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:33:19 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/07 16:34:49 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_image(t_mlx_data *mlx, t_scene *scene)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < WIN_H)
	{
		while (x < WIN_W)
		{

			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img_st->img, 0, 0);
}
