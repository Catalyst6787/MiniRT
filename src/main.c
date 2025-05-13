/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:00:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/14 00:45:34 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_img_data	img;
	t_scene		scene;

	t_minirt	minirt;

	ft_memset(&mlx, '\0', sizeof(t_mlx_data));
	ft_memset(&img, '\0', sizeof(t_img_data));
	ft_memset(&scene, '\0', sizeof(t_scene));

	minirt.mlx = &mlx;
	minirt.scene = &scene;
	minirt.img = &img;
	if (ac != 2)
		return (ft_printf("Usage: <scene.rt>\n"), 1);

	parse_scene(&minirt, av[1]);
	if (WIN_H < 10 || WIN_W < 10)
		quit(&minirt, WIN_SIZE_ERR);
	if (init_structure(&mlx, &img))
		quit(&minirt, MLX_ERR);
	if (init_events(&mlx))  //?
		quit(&minirt,"Event initialisation failed\n");

	clock_t t;
	t = clock();

	render_scene(&minirt, &mlx, &scene);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("rendered image in %f seconds\n", time_taken);
	mlx_loop(mlx.mlx);
	CLOSE_DEBUG_FD;
	quit(&minirt, "Quiting program\n");
	return (0);
}
