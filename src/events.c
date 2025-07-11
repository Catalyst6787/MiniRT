
#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	(void) mlx;
	#ifndef __APPLE__
	mlx_loop_end(mlx->mlx);
	#endif
	return (0);
}

void	number_handle(int keycode, t_minirt *minirt)
{
	int	number;

	number = keycode - 48;
	printf("special scene: %d loading...\n", number);
	load_special_scene(number, minirt);
	render_scene(minirt);
}

void	event_render(t_minirt *minirt)
{
	clock_t	t;
	double	time_taken;

	ft_printf("Spacebar pressed : render asked!\n");
	minirt->render->pixel_size = 1;
	t = clock();
	render_scene(minirt);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("Scene rendered in %f seconds\n", time_taken);
}

void	event_display_command_help(t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (minirt->ui->command_help)
		minirt->ui->command_help = 0;
	else
		minirt->ui->command_help = 1;
	render_scene(minirt);
}

void	event_change_string_color(t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (!minirt->ui->color_id)
	{
		minirt->ui->string_color = get_color(0, 0, 0);
		minirt->ui->color_id++;
	}
	else if (minirt->ui->color_id == 1)
	{
		minirt->ui->string_color = get_color(1, 0, 0);
		minirt->ui->color_id++;
	}
	else if (minirt->ui->color_id == 2)
	{
		minirt->ui->string_color = get_color(1, 1, 1);
		minirt->ui->color_id = 0;
	}
	render_scene(minirt);
}

void	set_selected_object_str(t_minirt *minirt, t_scene *scene)
{
	char	*tmp;
	char	*nb;

	tmp = object_type_to_str(&scene->objects[minirt->ui->selected_object], 1);
	if (!tmp)
		quit(minirt, MALLOC_ERR);
	nb = ft_itoa(scene->objects[minirt->ui->selected_object].id);
	if (!nb)
	{
		free(tmp);
		quit(minirt, MALLOC_ERR);
	}
	minirt->ui->str_selected_object = ft_strjoin (tmp, nb);
	free(tmp);
	free(nb);
	if (!minirt->ui->str_selected_object)
		quit(minirt, MALLOC_ERR);
	tmp = NULL;
	nb = NULL;
}

static void	switch_pav_mode(t_minirt *minirt)
{
	if (minirt->ui->move_mode == dir)
	{
		minirt->ui->move_mode = pos;
		printf("pos mode selected\n");
	}
	else if (minirt->ui->move_mode == pos)
	{
		minirt->ui->move_mode = dir;
		printf("dir mode selected\n");
	}
}

void	event_object_selection(t_minirt *minirt, t_scene *scene, int keycode)
{
	if (keycode == PAV_MINUS)
	{
		if (minirt->ui->selected_object == 0)
			minirt->ui->selected_object = minirt->scene->nb_objects - 1;
		else if (minirt->ui->selected_object > 0)
			minirt->ui->selected_object--;
		set_selected_object_str(minirt, scene);
	}
	else if (keycode == PAV_PLUS)
	{
		if (minirt->ui->selected_object < minirt->scene->nb_objects - 1)
			minirt->ui->selected_object++;
		else if (minirt->ui->selected_object == minirt->scene->nb_objects - 1)
			minirt->ui->selected_object = 0;
		set_selected_object_str(minirt, scene);
	}
	else if (keycode == PAV_MIDDLE)
		switch_pav_mode(minirt);
	render_scene(minirt);
}

static void handle_arrows_mac_linux(int keycode, t_minirt *minirt)
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
	if (keycode >= 48 && keycode <= 57)
		number_handle(keycode, minirt);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
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

