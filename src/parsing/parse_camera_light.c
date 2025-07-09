#include "matrice.h"
#include "minirt.h"
#include "vec3.h"

int	count_comas(char *buffer, int i)
{
	int	count;

	count = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] == ',')
			count++;
		i++;
	}
	return (count);
}


int	parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 2)
		quit(minirt, WRONG_AMB_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]))
		i++;
	scene->ambient->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->ambient->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.b = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->ambient->color.g = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->ambient->color.w = 0;
	*cursor = i;
	return (1);
	//check
}

int	parse_camera(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4)
		quit(minirt, WRONG_CAM_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->camera->view.from.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.from.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.from.w = 1;
	scene->camera->view.to.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.to.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->camera->view.to.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->camera->view.to.w = 1;
	scene->camera->view.up = get_vec3(0, 1, 0);
	scene->camera->hsize = WIN_W;
	scene->camera->vsize = WIN_H;
	scene->camera->fov = (int)ato_buffer(&scene->buffer[i], &i, '\n');
	set_pixel_size(scene->camera);
	scene->camera->transform = get_orientation_matrix(scene->camera->view);
	scene->camera->inv = get_inversed_matrix(scene->camera->transform);
	*cursor = i;
	return (1);
	//check
}

int	parse_light(t_minirt *minirt, t_scene *scene, int *cursor)
{
	int	i;

	i = *cursor + 1;
	if (count_comas(scene->buffer, i) != 4)
		quit(minirt, WRONG_LIGHT_DATA);
	while (scene->buffer[i] && !ft_isalnum(scene->buffer[i]) && scene->buffer[i] != '-')
		i++;
	scene->light->pos.x = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos.y = ato_buffer(&scene->buffer[i], &i, ',');
	scene->light->pos.z = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->pos.w = 1;
	scene->light->brightness = ato_buffer(&scene->buffer[i], &i, ' ');
	scene->light->color.r = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->light->color.g = ato_buffer(&scene->buffer[i], &i, ',') / 255;
	scene->light->color.b = ato_buffer(&scene->buffer[i], &i, '\n') / 255;
	scene->light->color.w = 0;
	*cursor = i;
	return (1);
	//check
}
