#include "minirt.h"

static void	handle_object(t_object *object, t_move_mode color, int keycode)
{
	if (color == red)
	{
		if (keycode == PAV_UP && object->material.color.r < 0.98)
			object->material.color.r += 0.02;
		else if (keycode == PAV_DOWN && object->material.color.r > 0.02)
			object->material.color.r -= 0.02;
	}
	else if (color == green)
	{
		if (keycode == PAV_UP && object->material.color.g < 0.98)
			object->material.color.g += 0.02;
		else if (keycode == PAV_DOWN && object->material.color.g > 0.02)
			object->material.color.g -= 0.02;
	}
	else if (color == blue)
	{
		if (keycode == PAV_UP && object->material.color.b < 0.98)
			object->material.color.b += 0.02;
		else if (keycode == PAV_DOWN && object->material.color.b > 0.02)
			object->material.color.b -= 0.02;
	}
}

static void	handle_lights(t_light *light, t_move_mode color, int keycode, int i)
{
	if (color == red)
	{
		if (keycode == PAV_UP && light->color.r < 0.98)
			light->color.r += 0.02;
		else if (keycode == PAV_DOWN && light->color.r > 0.02)
			light->color.r -= 0.02;
		printf("Light[%d] r : %.2f\n", i, light->color.r);
	}
	else if (color == green)
	{
		if (keycode == PAV_UP && light->color.g < 0.98)
			light->color.g += 0.02;
		else if (keycode == PAV_DOWN && light->color.g > 0.02)
			light->color.g -= 0.02;
		printf("Light[%d] g : %.2f\n", i, light->color.g);
	}
	else if (color == blue)
	{
		if (keycode == PAV_UP && light->color.b < 0.98)
			light->color.b += 0.02;
		else if (keycode == PAV_DOWN && light->color.b > 0.02)
			light->color.b -= 0.02;
		printf("Light[%d] b : %.2f\n", i, light->color.b);
	}
}

void	set_obj_amb_color(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nb_objects)
	{
		scene->objects[i].material.ambient_color = scene->ambient->color;
		i++;
	}
}

static void	handle_ambient(t_scene *scene,
							t_ambient *ambient,
							t_move_mode color,
							int keycode)
{
	if (color == red)
	{
		if (keycode == PAV_UP && ambient->color.r < 0.98)
			ambient->color.r += 0.02;
		else if (keycode == PAV_DOWN && ambient->color.r >= 0.02)
			ambient->color.r -= 0.02;
		printf("Amb r : %.2f\n", ambient->color.r);
	}
	else if (color == green)
	{
		if (keycode == PAV_UP && ambient->color.g < 0.98)
			ambient->color.g += 0.02;
		else if (keycode == PAV_DOWN && ambient->color.g >= 0.02)
			ambient->color.g -= 0.02;
		printf("Amb g : %.2f\n", ambient->color.g);
	}
	else if (color == blue)
	{
		if (keycode == PAV_UP && ambient->color.b < 0.98)
			ambient->color.b += 0.02;
		else if (keycode == PAV_DOWN && ambient->color.b >= 0.02)
			ambient->color.b -= 0.02;
		printf("Amb b : %.2f\n", ambient->color.b);
	}
	set_obj_amb_color(scene);
}

void	change_element_color(t_minirt *minirt, t_ui *ui, int keycode, int i)
{
	if (ui->selected_type == OBJ)
	{
		handle_object(&minirt->scene->objects[i], ui->move_mode, keycode);
	}
	else if (ui->selected_type == LIGHT)
		handle_lights(minirt->scene->lights[i - minirt->scene->nb_objects],
			ui->move_mode, keycode, i);
	else
		handle_ambient(minirt->scene, minirt->scene->ambient,
			ui->move_mode, keycode);
}
