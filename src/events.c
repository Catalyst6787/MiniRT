
#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	(void) mlx;
	mlx_loop_end(mlx->mlx);
	return (0);
}


void	arrows_handle(int keycode, t_minirt *minirt)
{
	if (keycode == UP)
	{
		ft_printf("[↑] pressed\n");
		minirt->scene->camera->dir->y += 0.05;
	}
	else if (keycode == DOWN)
	{
		ft_printf("[↓] pressed\n");
		minirt->scene->camera->dir->y -= 0.05;
	}
	else if (keycode == LEFT)
	{
		ft_printf("[←] pressed\n");
		minirt->scene->camera->dir->x -= 0.05;
	}
	else if (keycode == RIGHT)
	{
		ft_printf("[→] pressed\n");
		minirt->scene->camera->dir->x += 0.05;
	}
	render_scene(minirt);
}

void	asdw_handle(int keycode, t_minirt *minirt)
{
	if (keycode == W)
		minirt->scene->camera->pos->z += 0.05;
	else if (keycode == A)
		minirt->scene->camera->pos->x -= 0.05;
	else if (keycode == S)
		minirt->scene->camera->pos->z -= 0.05;
	else if (keycode == D)
		minirt->scene->camera->pos->x += 0.05;
	ft_printf("[%c] pressed\n", keycode - 32);
	render_scene(minirt);
}



int	handle_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == Q || keycode == ESC)
		end_mlx_loop(minirt->mlx);
	if (65361 <= keycode && keycode <= 65364)
		arrows_handle(keycode, minirt);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		asdw_handle(keycode, minirt);
	else if (keycode == E)
	{
		minirt->scene->camera->pos->y += 0.05;
		ft_printf("[E] pressed\n");
	}
	else if (keycode == R)
	{
		minirt->scene->camera->pos->y -= 0.05;
		ft_printf("[R] pressed\n");
	}
	else if (keycode == SPACE)
		ft_printf("space pressed\n");
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
