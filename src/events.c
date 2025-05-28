
#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	(void) mlx;
	mlx_loop_end(mlx->mlx);
	return (0);
}


void	arrows_handle(int keycode, t_minirt *minirt)
{
	if (keycode == UP && minirt->scene->camera->dir->y < 1.0)
	{
		ft_printf("[↑] pressed\n");
		minirt->scene->camera->dir->y += 0.1;
	}
	else if (keycode == DOWN && minirt->scene->camera->dir->y > 0.0)
	{
		ft_printf("[↓] pressed\n");
		minirt->scene->camera->dir->y -= 0.1;
	}
	else if (keycode == LEFT  && minirt->scene->camera->dir->x > 0.0)
	{
		ft_printf("[←] pressed\n");
		minirt->scene->camera->dir->x -= 0.1;
	}
	else if (keycode == RIGHT && minirt->scene->camera->dir->x < 1.0)
	{
		ft_printf("[→] pressed\n");
		minirt->scene->camera->dir->x += 0.1;
	}
	init_render(minirt);
	render_scene(minirt);
}

void	asdw_handle(int keycode, t_minirt *minirt)
{
	if (keycode == W)
		minirt->scene->camera->pos->z += 0.1;
	else if (keycode == A)
		minirt->scene->camera->pos->x -= 0.1;
	else if (keycode == S)
		minirt->scene->camera->pos->z -= 0.1;
	else if (keycode == D)
		minirt->scene->camera->pos->x += 0.1;
	else if (keycode == E)
		minirt->scene->camera->pos->y += 0.1;
	else if (keycode == R)
		minirt->scene->camera->pos->y -= 0.05;
	ft_printf("[%c] pressed\n", keycode - 32);
	init_render(minirt);
	render_scene(minirt);
}

int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == Q || keycode == ESC)
		end_mlx_loop(minirt->mlx);
	if (65361 <= keycode && keycode <= 65364)
		arrows_handle(keycode, minirt);
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == E || keycode == R)
		asdw_handle(keycode, minirt);
	else if (keycode == SPACE)
		event_print_debug(minirt);
	else if (keycode == C)
		print_camera_data(minirt);
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
