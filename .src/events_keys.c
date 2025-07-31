#include "minirt.h"

static void	handle_arrows_mac_linux(int keycode, t_minirt *minirt)
{
	#ifdef __linux__
	if ((65360.5 <= keycode && keycode <= 65364))
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		arrows_handle(keycode, minirt);
	}
	#endif
	#ifdef __APPLE__
	if ((123 <= keycode && keycode <= 126)
		|| keycode == 24 || keycode == 27)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		arrows_handle(keycode, minirt);
	}
	#endif
}

static void	handle_extra(int keycode, t_minirt *minirt)
{
	if (keycode == PAV_MINUS || keycode == PAV_PLUS
		|| keycode == PAV_MIDDLE)
		event_object_selection(minirt, minirt->scene, keycode);
	else if (keycode == P && minirt->scene->nb_sphere)
		event_sphere_shearing(minirt);
	else if (keycode == L && minirt->scene->nb_cylinder)
	{
		printf("[L] pressed\n");
		event_turn_cylinders(minirt);
	}
	else if (keycode == V)
		event_activate_cylinder_cap(minirt);
	else if (keycode == B)
		event_display_command_help(minirt);
	else if (keycode == N)
		event_change_string_color(minirt);
	else if (keycode == C)
		event_print_debug(minirt);
	else if (keycode == Q)
	{
	}
	else if (keycode == SPACE)
		event_render(minirt);
	else
		ft_printf("unknow action: %d\n", keycode);
}

int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == ESC)
		end_mlx_loop(minirt->mlx);
	handle_arrows_mac_linux(keycode, minirt);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		asdw_handle(keycode, minirt);
	}
	else if (keycode == E || keycode == R || keycode == Z || keycode == X)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		erzx_handle(keycode, minirt);
	}
	else if (keycode == U || keycode == H || keycode == J
		|| keycode == K || keycode == I || keycode == O)
		event_light_pos(minirt, keycode);
	else if (65429.9 <= keycode && keycode <= 65435.5)
		event_obj_pos(minirt, keycode);
	handle_extra(keycode, minirt);
	return (0);
}

int	handle_mouseclick(int button, int x, int y, t_minirt *minirt)
{
	(void) minirt;
	ft_printf("Mouseclick at: x=%d, y=%d, Button:%d\n", x, y, button);
	return (0);
}
