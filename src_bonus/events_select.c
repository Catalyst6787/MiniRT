#include "minirt.h"

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
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
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
