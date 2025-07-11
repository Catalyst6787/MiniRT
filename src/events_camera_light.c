#include "minirt.h"

void	event_light_pos(t_minirt *minirt, int keycode)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == U)
		minirt->scene->light->pos.y += 0.2;
	else if (keycode == H)
		minirt->scene->light->pos.x -= 0.2;
	else if (keycode == J)
		minirt->scene->light->pos.y -= 0.2;
	else if (keycode == K)
		minirt->scene->light->pos.x += 0.2;
	else if (keycode == I)
		minirt->scene->light->pos.z -= 0.2;
	else if (keycode == O)
		minirt->scene->light->pos.z += 0.2;
	render_scene(minirt);
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
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	render_scene(minirt);
}

void	erzx_handle(int keycode, t_minirt *minirt)
{
	if (keycode == E)
	{
		minirt->scene->camera->view.from.y += 0.5;
		minirt->scene->camera->view.to.y += 0.5;
	}
	else if (keycode == R)
	{
		minirt->scene->camera->view.from.y -= 0.5;
		minirt->scene->camera->view.to.y -= 0.5;
	}
	else if (keycode == Z)
		minirt->scene->camera->view.to.z -= 0.5;
	else if (keycode == X)
		minirt->scene->camera->view.to.z += 0.5;
	ft_printf("[%c] pressed\n", keycode - 32);
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	render_scene(minirt);
}

int	asdw_handle(int keycode, t_minirt *minirt)
{
	if (keycode == W)
	{
		minirt->scene->camera->view.from.z += 0.5;
		minirt->scene->camera->view.to.z += 0.5;
	}
	else if (keycode == A)
	{
		minirt->scene->camera->view.from.x -= 0.5;
		minirt->scene->camera->view.to.x -= 0.5;
	}
	else if (keycode == S)
	{
		minirt->scene->camera->view.from.z -= 0.5;
		minirt->scene->camera->view.to.z -= 0.5;
	}
	else if (keycode == D)
	{
		minirt->scene->camera->view.from.x += 0.5;
		minirt->scene->camera->view.to.x += 0.5;
	}
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	return (ft_printf("[%c] pressed\n", keycode - 32), render_scene(minirt));
}
