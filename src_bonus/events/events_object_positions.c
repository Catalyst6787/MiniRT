#include "minirt.h"

void	event_handle_pavnum(t_minirt *minirt, int keycode)
{
	int	i;

	i = minirt->ui->selected_object;
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (minirt->ui->move_mode == pos)
		change_element_position(minirt, minirt->ui, keycode, i);
	else if (minirt->ui->move_mode == dir)
		change_element_direction(minirt, minirt->ui, keycode, i);
	else if (minirt->ui->move_mode == size && minirt->ui->selected_type == OBJ && minirt->scene->objects[i].type != PLANE)
		change_element_size(minirt->scene, keycode, i);
	else if (minirt->ui->move_mode >= red && minirt->ui->move_mode <= blue)
		change_element_color(minirt, minirt->ui, keycode, i);
	start_render(minirt);
}
