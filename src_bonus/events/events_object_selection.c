#include "minirt.h"

int	select_ambient(t_minirt *minirt)
{
	minirt->ui->str_selected_object = ft_strdup("Selected : ambiant");
		if (!minirt->ui->str_selected_object)
			quit(minirt, MALLOC_ERR);
	return (0);
}

void	select_objects(t_minirt *minirt, t_scene *scene, char **tmp, char **nb)
{
	if (minirt->ui->selected_object >= scene->nb_objects)
	{
		*tmp = ft_strdup("Selected : light ");
		*nb = ft_itoa(minirt->ui->selected_object - scene->nb_objects);
	}
	else if (minirt->ui->selected_object < scene->nb_objects)
	{
		*tmp = object_type_to_str(&scene->objects[minirt->ui->selected_object]);
		*nb = ft_itoa(scene->objects[minirt->ui->selected_object].id);
	}
	if (!tmp)
		quit(minirt, MALLOC_ERR);
	if (!nb)
	{
		free(tmp);
		quit(minirt, MALLOC_ERR);
	}
}

int	set_selected_object_data(t_minirt *minirt, t_scene *scene)
{
	char	*tmp;
	char	*nb;
	
	if (minirt->ui->str_selected_object)
		free_and_null((void**)&minirt->ui->str_selected_object);
	if (minirt->ui->selected_object == scene->nb_objects + scene->nb_light)
	{
		minirt->ui->selected_type = AMB;
		return (select_ambient(minirt));
	}
	select_objects(minirt, minirt->scene, &tmp, &nb);
	minirt->ui->str_selected_object = ft_strjoin(tmp, nb);
	free(tmp);
	free(nb);
	if (!minirt->ui->str_selected_object)
		quit(minirt, MALLOC_ERR);
	if (minirt->ui->selected_object < scene->nb_objects)
		minirt->ui->selected_type = OBJ;
	else
		minirt->ui->selected_type = LIGHT;
	return (0);
}

static void	switch_pav_mode(t_minirt *minirt)
{
	if (minirt->ui->str_mode)
		free_and_null((void**)&minirt->ui->str_mode);
	if (minirt->ui->move_mode == 5)
		minirt->ui->move_mode = 0;
	else
		minirt->ui->move_mode ++;
	if (minirt->ui->move_mode == dir)
		minirt->ui->str_mode = ft_strdup("Mode : direction");
	else if (minirt->ui->move_mode == pos)
		minirt->ui->str_mode = ft_strdup("Mode : position");
	else if (minirt->ui->move_mode == size)
		minirt->ui->str_mode = ft_strdup("Mode : size");
	else if (minirt->ui->move_mode == red)
		minirt->ui->str_mode = ft_strdup("Mode : red");
	else if (minirt->ui->move_mode == green)
		minirt->ui->str_mode = ft_strdup("Mode : green");
	else if (minirt->ui->move_mode == blue)
		minirt->ui->str_mode = ft_strdup("Mode : blue");
	if (!minirt->ui->str_mode)
		quit(minirt, MALLOC_ERR);
}

void	event_object_selection(t_minirt *minirt, t_scene *scene, int keycode)
{
	minirt->render->pixel_size = PIXEL_SIZE_MULT;
	if (keycode == PAV_MINUS)
	{
		if (minirt->ui->selected_object == 0)
			minirt->ui->selected_object = scene->nb_objects + scene->nb_light;
		else if (minirt->ui->selected_object > 0)
			minirt->ui->selected_object--;
		set_selected_object_data(minirt, scene);
	}
	else if (keycode == PAV_PLUS)
	{
		if (minirt->ui->selected_object < scene->nb_objects + scene->nb_light)
			minirt->ui->selected_object++;
		else
			minirt->ui->selected_object = 0;
		set_selected_object_data(minirt, scene);
	}
	else if (keycode == PAV_MIDDLE)
		switch_pav_mode(minirt);
	printf("Selected : %d (type %d)\n", minirt->ui->selected_object, minirt->ui->selected_type);
	start_render(minirt);
}
