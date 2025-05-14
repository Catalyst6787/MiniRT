/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:22:34 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/14 12:03:25 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quit(t_mlx_data *mlx)
{
	if (mlx && mlx->mlx)
	{
		mlx_clear_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_image(mlx->mlx, mlx->img_st->img);
		mlx->img_st->addr = NULL;
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
	exit(0);
}
