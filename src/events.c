
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
	int number;

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

void	set_selected_object_str(t_minirt *minirt, t_scene *scene)
{
	char	*tmp;
	char	*nb;

	tmp = object_type_to_str(&scene->objects[minirt->mlx->selected_object], 1);
	if (!tmp)
		quit(minirt, MALLOC_ERR);
	nb = ft_itoa(scene->objects[minirt->mlx->selected_object].id);
	if (!nb)
	{
		free(tmp);
		quit(minirt, MALLOC_ERR);
	}
	minirt->mlx->str_selected_object = ft_strjoin (tmp, nb);
	free(tmp);
	free(nb);
	if (!minirt->mlx->str_selected_object)
		quit(minirt, MALLOC_ERR);
	tmp = NULL;
	nb = NULL;
}	

void	event_object_selection(t_minirt *minirt, t_scene *scene, int keycode)
{
	if (keycode == PAV_MINUS)
	{
		if (minirt->mlx->selected_object == 0)
			minirt->mlx->selected_object = minirt->scene->nb_objects - 1;
		else if (minirt->mlx->selected_object > 0)
			minirt->mlx->selected_object--;
		set_selected_object_str(minirt, scene);
	}
	else if (keycode == PAV_PLUS)
	{
		if (minirt->mlx->selected_object < minirt->scene->nb_objects - 1)
			minirt->mlx->selected_object++;
		else if (minirt->mlx->selected_object == minirt->scene->nb_objects - 1)
			minirt->mlx->selected_object = 0;
		set_selected_object_str(minirt, scene);
	}
	else if (keycode == PAV_MIDDLE)
	{
		if (minirt->mlx->move_mode == dir)
		{
			minirt->mlx->move_mode = pos;
			printf("pos mode selected\n");
		}
		else if (minirt->mlx->move_mode == pos)
		{
			minirt->mlx->move_mode = dir;
			printf("dir mode selected\n");
		}
	}
	render_scene(minirt);
}


int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == ESC)
		end_mlx_loop(minirt->mlx);

	#ifdef __linux__
	else if ((65360.5 <= keycode && keycode <= 65364))
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		arrows_handle(keycode, minirt);
	}
	else if (keycode >= 48 && keycode <= 57)
		number_handle(keycode, minirt);
	#endif
	#ifdef __APPLE__
	else if ((123 <= keycode && keycode <= 126) || keycode == 24 || keycode == 27)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		arrows_handle(keycode, minirt);
	}
	#endif

	else if (keycode == W || keycode == A || keycode == S || keycode == D
			|| keycode == E || keycode == R || keycode == Z || keycode == X)
	{
		minirt->render->pixel_size = PIXEL_SIZE_MULT;
		asdw_handle(keycode, minirt);
	}
	else if (keycode == U || keycode == H || keycode == J
			|| keycode == K || keycode == I || keycode == O)
		event_light_pos(minirt, keycode);
	else if (65429.9 <= keycode && keycode <= 65435.5)
		event_obj_pos(minirt, keycode);
	else if (keycode == PAV_MINUS || keycode == PAV_PLUS || keycode == PAV_MIDDLE)
	{
		event_object_selection(minirt, minirt->scene, keycode);
	}
	else if (keycode == P && minirt->scene->nb_sphere)
	{
		printf("[P] pressed\n");
		if (minirt->render->pixel_size == PIXEL_SIZE_MULT)
			event_sphere_shearing(minirt);
	}
	else if (keycode == L && minirt->scene->nb_cylinder)
	{
			printf("[L] pressed\n");
			if (minirt->render->pixel_size == PIXEL_SIZE_MULT)
				event_turn_cylinders(minirt);
	}
	else if (keycode == C)
		event_print_debug(minirt);
	else if (keycode == Q)
	{
	}
	else if (keycode == SPACE)
		event_render(minirt);
	else
		ft_printf("unknow action: %d\n", keycode);
	return (0);
}

int	handle_mouseclick(int button, int x, int y, t_minirt *minirt)
{
	(void) minirt;
	ft_printf("Mouseclick at: x=%d, y=%d, Button:%d\n", x, y, button);
	return (0);
}

