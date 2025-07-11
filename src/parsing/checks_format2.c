
#include "minirt.h"

void	check_file_name(t_minirt *minirt)
{
	int	i;

	i = 0;
	if (!ft_is_char_in_string(minirt->scene->filename, '.'))
		quit(minirt, EXT_MISSING_ERR);
	while (minirt->scene->filename[i] && minirt->scene->filename[i] != '.')
		i++;
	if (minirt->scene->filename[++i] != 'r')
		quit(minirt, WRONG_EXT_ERR);
	if (minirt->scene->filename[++i] != 't')
		quit(minirt, WRONG_EXT_ERR);
	if (minirt->scene->filename[++i])
		quit(minirt, WRONG_EXT_ERR);
}

void	single_elements_check(t_minirt *minirt, t_scene *scene)
{
	if (scene->nb_amb == 0)
		quit(minirt, MISSING_AMB_ERR);
	else if (scene->nb_amb > 1)
		quit(minirt, TOO_MANY_AMB_ERR);
	else if (scene->nb_cam == 0)
		quit(minirt, MISSING_CAM_ERR);
	else if (scene->nb_cam > 1)
		quit(minirt, TOO_MANY_CAM_ERR);
	else if (scene->nb_light == 0)
		quit(minirt, MISSING_LIGHT_ERR);
	else if (scene->nb_light > 1)
		quit(minirt, TOO_MANY_LIGHT_ERR);
}
