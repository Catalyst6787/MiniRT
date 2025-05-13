/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:22:34 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/13 17:28:22 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_exit_info(char *str)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd("(", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
	}
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	// if (DEBUG_MODE)
	// 	ft_putstr_fd("--------------------------\n\n", STDERR_FILENO );
}

int	quit(t_mlx_data *mlx)
{
	// print_exit_info(str);
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_image(mlx->mlx, mlx->img_st->img);
	mlx->img_st->addr = NULL;
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
