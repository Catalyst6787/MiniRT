#include "minirt.h"

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

// void	event_light_pos(t_minirt *minirt, int keycode)
// {
// 	printf("rework light pos to move multiple lights with select like for object\n");
// 	(void)minirt;
// 	(void)keycode;
// 	minirt->render->pixel_size = PIXEL_SIZE_MULT;
// 	if (!minirt->scene->nb_light)
// 		return ;
// 	if (keycode == U)
// 		minirt->scene->lights[0]->pos.y += 0.2;
// 	else if (keycode == H)
// 		minirt->scene->lights[0]->pos.x -= 0.2;
// 	else if (keycode == J)
// 		minirt->scene->lights[0]->pos.y -= 0.2;
// 	else if (keycode == K)
// 		minirt->scene->lights[0]->pos.x += 0.2;
// 	else if (keycode == I)
// 		minirt->scene->lights[0]->pos.z -= 0.2;
// 	else if (keycode == O)
// 		minirt->scene->lights[0]->pos.z += 0.2;
// 	start_render(minirt);
// }

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
		minirt->scene->camera->view.to.y += 0.5;
	else if (keycode == DOWN)
		minirt->scene->camera->view.to.y -= 0.5;
	else if (keycode == LEFT)
		minirt->scene->camera->view.to.x -= 0.5;
	else if (keycode == RIGHT)
		minirt->scene->camera->view.to.x += 0.5;
	print_arrows(keycode);
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
	minirt->scene->camera->transform
		= get_orientation_matrix(minirt->scene->camera->view);
	minirt->scene->camera->inv
		= get_inversed_matrix(minirt->scene->camera->transform);
	start_render(minirt);
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
	return (ft_printf("[%c] pressed\n", keycode - 32), start_render(minirt));
}
