/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:00:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 16:37:25 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_mlx_data	mlx;
	t_img_data	img;

	if (WIN_H < 10 || WIN_W < 10)
		return (ft_printf("Window sizes less than 10x10 are unsupported\n"), 1);
	if (init_structure(&mlx, &img))
		return (perror("Structure initialisation failed"), 1);
	if (init_events(&mlx))
		return (perror("Event initialisation failed"), quit(&mlx), 1);

	debug_aff_image(&mlx);
	mlx_loop(mlx.mlx);

	quit(&mlx);
	return (0);
}
