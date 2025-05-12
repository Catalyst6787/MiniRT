/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:00:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/12 11:43:53 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_img_data	img;
	t_scene		scene;

	ft_memset(&mlx, '\0', sizeof(t_mlx_data));
	ft_memset(&img, '\0', sizeof(t_img_data));
	ft_memset(&scene, '\0', sizeof(t_scene));
	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);
	if (parse(av[1], &scene))
		return (1);
	if (WIN_H < 10 || WIN_W < 10)
		return (ft_printf("Window sizes less than 10x10 are unsupported\n"), 1);
	if (init_structure(&mlx, &img))
		return (perror("Structure initialisation failed"), 1);
	if (init_events(&mlx))
		return (perror("Event initialisation failed"), quit(&mlx), 1);
	render_scene(&mlx, &scene);
	mlx_loop(mlx.mlx);

	quit(&mlx);
	return (0);
}
