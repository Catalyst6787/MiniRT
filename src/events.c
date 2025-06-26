
#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	(void) mlx;
	#ifndef __APPLE__
	mlx_loop_end(mlx->mlx);
	#endif

	return (0);
}


void	arrows_handle(int keycode, t_minirt *minirt)
{
	if (keycode == UP)
	{
		ft_printf("[↑] pressed\n");
		minirt->scene->camera->view.to.y += 0.5;
	}
	else if (keycode == DOWN)
	{
		ft_printf("[↓] pressed\n");
		minirt->scene->camera->view.to.y -= 0.5;
	}
	else if (keycode == LEFT)
	{
		ft_printf("[←] pressed\n");
		minirt->scene->camera->view.to.x -= 0.5;
	}
	else if (keycode == RIGHT)
	{
		ft_printf("[→] pressed\n");
		minirt->scene->camera->view.to.x += 0.5;
	}
	else if (keycode == PLUS)
	{
		ft_printf("[+] pressed\n");
		minirt->scene->camera->view.to.z += 0.5;
	}
	else if (keycode == MINUS)
	{
		ft_printf("[-] pressed\n");
		minirt->scene->camera->view.to.z -= 0.5;
	}
	minirt->scene->camera->transform = get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv = get_inversed_matrix(minirt->scene->camera->transform);
	render_scene(minirt);
}

void	asdw_handle(int keycode, t_minirt *minirt)
{
	if (keycode == S)
	{
		minirt->scene->camera->view.from.z -= 0.5;
		minirt->scene->camera->view.to.z -= 0.5;
	}
	else if (keycode == A)
	{
		minirt->scene->camera->view.from.x -= 0.5;
		minirt->scene->camera->view.to.x -= 0.5;
	}
	else if (keycode == W)
	{
		minirt->scene->camera->view.from.z += 0.5;
		minirt->scene->camera->view.to.z += 0.5;
	}
	else if (keycode == D)
	{
		minirt->scene->camera->view.from.x += 0.5;
		minirt->scene->camera->view.to.x += 0.5;
	}
	else if (keycode == E)
	{
		minirt->scene->camera->view.from.y += 0.5;
		minirt->scene->camera->view.to.y += 0.5;
	}
	else if (keycode == R)
	{
		minirt->scene->camera->view.from.y -= 0.5;
		minirt->scene->camera->view.to.y -= 0.5;
	}
	ft_printf("[%c] pressed\n", keycode - 32);
	minirt->scene->camera->transform = get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv = get_inversed_matrix(minirt->scene->camera->transform);
	render_scene(minirt);
}

void	number_handle(int keycode, t_minirt *minirt)
{
	int number;

	number = keycode - 48;
	printf("special scene: %d loading...\n", number);
	load_special_scene(number, minirt);
	render_scene(minirt);
}

int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == Q || keycode == ESC)
		end_mlx_loop(minirt->mlx);
	if ((65360.5 <= keycode && keycode <= 65364) || keycode == 45 || keycode == 60.5)
		arrows_handle(keycode, minirt);
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == E || keycode == R)
		asdw_handle(keycode, minirt);
	else if (keycode == SPACE)
		event_print_debug(minirt);
	else if (keycode == C)
		print_camera_data(minirt);
	else if (keycode >= 48 && keycode <= 57)
		number_handle(keycode, minirt);
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
