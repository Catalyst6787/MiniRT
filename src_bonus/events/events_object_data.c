#include "minirt.h"

int	is_brightness_change_ok(t_scene *scene)
{
	int		i;
	double	tot;

	i = 0;
	tot = scene->ambient->brightness + 0.02;
	while (i < scene->nb_light)
	{
		tot += scene->lights[i]->brightness;
		i++;
	}
	if (tot > 1)
	{
		printf("Total light : max value reached\n");
		return (0);
	}
	return (1);
}

void	change_light_brightness(t_scene *scene, int keycode, int i)
{
	i -= scene->nb_objects;
	if (keycode == PAV_UP && scene->lights[i]->brightness < 0.98)
	{
		if (!is_brightness_change_ok(scene))
			return ;
		scene->lights[i]->brightness += 0.02;
		printf("Light[%d] : %.2f\n", i, scene->lights[i]->brightness);
	}
	else if (keycode == PAV_DOWN && scene->lights[i]->brightness > 0.02)
	{
		scene->lights[i]->brightness -= 0.02;
		printf("Light[%d] : %.2f\n", i, scene->lights[i]->brightness);
	}
}

void	change_amb_brightness(t_scene *scene, int keycode)
{
	if (keycode == PAV_UP && scene->ambient->brightness < 0.98)
	{
		if (!is_brightness_change_ok(scene))
			return ;
		scene->ambient->brightness += 0.02;
		printf("Amb : %.2f\n", scene->ambient->brightness);
		// set_object_ambient_light(scene); #TODO convert to object ambient light
	}
	else if (keycode == PAV_DOWN && scene->ambient->brightness > 0.02)
	{
		scene->ambient->brightness -= 0.02;
		// set_object_ambient_light(scene); #TODO convert to object ambient light
		printf("Amb : %.2f\n", scene->ambient->brightness);
	}
}

void	event_handle_pavnum(t_minirt *minirt, int keycode)
{
	int	i;

	i = minirt->ui->selected_object;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (minirt->ui->move_mode == pos)
		change_element_position(minirt, minirt->ui, keycode, i);
	else if (minirt->ui->move_mode == dir)
		change_element_rotation(minirt, minirt->ui, keycode, i);
	else if (minirt->ui->move_mode == size && minirt->ui->selected_type == OBJ
		&& minirt->scene->objects[i].type != PLANE)
		change_element_size(minirt->scene, keycode, i);
	else if (minirt->ui->move_mode == bright)
	{
		if (minirt->ui->selected_type == LIGHT)
			change_light_brightness(minirt->scene, keycode, i);
		if (minirt->ui->selected_type == AMB)
			change_amb_brightness(minirt->scene, keycode);
	}
	else if (minirt->ui->move_mode >= red && minirt->ui->move_mode <= blue)
		change_element_color(minirt, minirt->ui, keycode, i);
	start_render(minirt);
}
