/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:51:16 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:51:17 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_extra(int keycode, t_minirt *minirt)
{
	if (keycode == P && minirt->scene->nb_sphere)
		event_sphere_shearing(minirt);
	else if (keycode == L && minirt->scene->nb_cylinder)
		event_turn_cylinders(minirt);
	else if (keycode == V)
		event_activate_cylinder_cap(minirt);
	else if (keycode == B)
		event_display_command_help(minirt);
	else if (keycode == N)
		event_change_string_color(minirt);
	else if (keycode == C)
		event_print_debug(minirt);
	else if (keycode == Q)
		save_random_scene(minirt);
	else
		ft_printf("Keycode [%d]\n", keycode);
}

int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == ESC)
		end_mlx_loop(minirt->mlx);
	else if (keycode == SPACE)
		event_render(minirt);
	else if ((LEFT <= keycode && keycode <= DOWN))
		arrows_handle(keycode, minirt);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		asdw_handle(keycode, minirt);
	}
	else if (keycode == E || keycode == R)
		erzx_handle(keycode, minirt);
	else if (keycode == PAV_MINUS || keycode == PAV_PLUS
		|| keycode == PAV_MIDDLE)
		event_object_selection(minirt, minirt->scene, keycode);
	else if (PAV_LEFT <= keycode && keycode <= PAV_BACK)
		event_handle_pavnum(minirt, keycode);
	else if (keycode == L_BRACKET || keycode == R_BRACKET)
		event_reflections(minirt, keycode);
	else
		handle_extra(keycode, minirt);
	return (0);
}

int	handle_mouseclick(int button, int x, int y, t_minirt *minirt)
{
	(void) minirt;
	ft_printf("Mouseclick [%d, %d] - Button:%d\n", x, y, button);
	return (0);
}
