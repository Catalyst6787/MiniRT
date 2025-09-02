/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:50:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:50:58 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <stdio.h>

void	event_reflections(t_minirt *minirt, int keycode)
{
	if (keycode == L_BRACKET)
	{
		if (minirt->render->max_depth > 0)
		{
			minirt->render->pixel_size = PIXEL_SIZE_MULT;
			minirt->render->max_depth --;
			printf("Max depth -- [%d]\n", minirt->render->max_depth);
			start_render(minirt);
		}
	}
	if (keycode == R_BRACKET)
	{
		if (minirt->render->max_depth < 15)
		{
			minirt->render->pixel_size = PIXEL_SIZE_MULT;
			minirt->render->max_depth ++;
			printf("Max depth ++ [%d]\n", minirt->render->max_depth);
			start_render(minirt);
		}
	}
}

void	print_arrows(int keycode)
{
	if (keycode == UP)
		ft_printf("[↑] pressed\n");
	else if (keycode == DOWN)
		ft_printf("[↓] pressed\n");
	else if (keycode == LEFT)
		ft_printf("[←] pressed\n");
	else if (keycode == RIGHT)
		ft_printf("[→] pressed\n");
}

void	arrows_handle(int keycode, t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == UP)
		minirt->scene->camera->view.pitch += 0.1;
	else if (keycode == DOWN)
		minirt->scene->camera->view.pitch -= 0.1;
	else if (keycode == LEFT)
		minirt->scene->camera->view.yaw += 0.1;
	else if (keycode == RIGHT)
		minirt->scene->camera->view.yaw -= 0.1;
	print_arrows(keycode);
	if (minirt->scene->camera->view.pitch > PITCH_LIMIT)
		minirt->scene->camera->view.pitch = PITCH_LIMIT;
	else if (minirt->scene->camera->view.pitch < -PITCH_LIMIT)
		minirt->scene->camera->view.pitch = -PITCH_LIMIT;
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	start_render(minirt);
}

void	erzx_handle(int keycode, t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == E)
		minirt->scene->camera->view.from.y += 0.5;
	else if (keycode == R)
		minirt->scene->camera->view.from.y -= 0.5;
	ft_printf("[%c] pressed\n", keycode - 32);
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	start_render(minirt);
}

int	asdw_handle(int keycode, t_minirt *minirt)
{
	t_vec3	right;

	minirt->scene->camera->view.dir = yaw_pitch_to_dir(minirt->scene->camera->view.yaw, minirt->scene->camera->view.pitch);
	right = vec3_normalise(vec3_cross(get_vec3(0, 1, 0), minirt->scene->camera->view.dir));
	if (keycode == W)
		minirt->scene->camera->view.from = vec3_vec_addition(minirt->scene->camera->view.from, vec3_double_multiplication(minirt->scene->camera->view.dir, 0.1));
	else if (keycode == A)
		minirt->scene->camera->view.from = vec3_vec_substraction(minirt->scene->camera->view.from, vec3_double_multiplication(right, 0.1));
	else if (keycode == S)
		minirt->scene->camera->view.from = vec3_vec_substraction(minirt->scene->camera->view.from, vec3_double_multiplication(minirt->scene->camera->view.dir, 0.1));
	else if (keycode == D)
		minirt->scene->camera->view.from = vec3_vec_addition(minirt->scene->camera->view.from, vec3_double_multiplication(right, 0.1));
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	return (ft_printf("[%c] pressed\n", keycode - 32), start_render(minirt));
}
