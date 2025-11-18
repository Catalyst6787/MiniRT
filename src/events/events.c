/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:29 by lfaure            #+#    #+#             */
/*   Updated: 2025/11/18 16:28:31 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

void	event_render(t_minirt *minirt)
{
	struct timeval	start_time;
	struct timeval	end_time;

	ft_printf("Spacebar pressed : render asked!\n");
	minirt->render->pixel_size = 1;
	gettimeofday(&start_time, NULL);
	start_render(minirt);
	gettimeofday(&end_time, NULL);
	printf("Scene rendered in %f seconds\n",
		(end_time.tv_sec - start_time.tv_sec)
		+ (end_time.tv_usec - start_time.tv_usec) / 1e6);
}

void	event_display_command_help(t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (minirt->ui->command_help)
	{
		minirt->ui->command_help = 0;
		printf("Hide command help\n");
	}
	else
	{
		minirt->ui->command_help = 1;
		printf("Show command help\n");
	}
	start_render(minirt);
}

void	event_change_string_color(t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (!minirt->ui->color_id)
	{
		minirt->ui->string_color = get_color(0, 0, 0);
		minirt->ui->color_id++;
		printf("String color changed to black\n");
	}
	else if (minirt->ui->color_id == 1)
	{
		minirt->ui->string_color = get_color(1, 0, 0);
		minirt->ui->color_id++;
		printf("String color changed to red\n");
	}
	else if (minirt->ui->color_id == 2)
	{
		minirt->ui->string_color = get_color(1, 1, 1);
		minirt->ui->color_id = 0;
		printf("String color changed to white\n");
	}
	start_render(minirt);
}
