#include "minirt.h"

int	end_mlx_loop(t_mlx_data *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

void	event_render(t_minirt *minirt)
{
	ft_printf("Spacebar pressed : render asked!\n");
	minirt->render->pixel_size = 1;
	start_render(minirt);
}

void	event_display_command_help(t_minirt *minirt)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (minirt->ui->command_help)
		minirt->ui->command_help = 0;
	else
		minirt->ui->command_help = 1;
	start_render(minirt);
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
	start_render(minirt);
}

void	set_selected_object_str(t_minirt *minirt, t_scene *scene)
{
	char	*tmp;
	char	*nb;
	
	if (minirt->ui->selected_object == scene->nb_objects + scene->nb_light)
	{
		minirt->ui->str_selected_object = ft_strdup("Selected : ambiant");
		if (!minirt->ui->str_selected_object)
			quit(minirt, MALLOC_ERR);
		return ;
	}
	if (minirt->ui->selected_object >= scene->nb_objects)
	{
		tmp = ft_strdup("Selected : light ");
		nb = ft_itoa(minirt->ui->selected_object - scene->nb_objects);
	}
	else if (minirt->ui->selected_object < scene->nb_objects)
	{
		tmp = object_type_to_str(&scene->objects[minirt->ui->selected_object]);
		nb = ft_itoa(scene->objects[minirt->ui->selected_object].id);
	}
	if (!tmp)
			quit(minirt, MALLOC_ERR);
	if (!nb)
	{
		free(tmp);
		quit(minirt, MALLOC_ERR);
	}
	minirt->ui->str_selected_object = ft_strjoin(tmp, nb);
	free(tmp);
	free(nb);
	if (!minirt->ui->str_selected_object)
		quit(minirt, MALLOC_ERR);
	tmp = NULL;
	nb = NULL;
}
