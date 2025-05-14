
#include "minirt.h"

void	check_file_name(t_minirt *minirt, char *file_path)
{
	int	i;

	i = 0;
	if (!ft_is_char_in_string(file_path, '.'))
		quit(minirt, EXT_MISSING_ERR);
	while (file_path[i] && file_path[i] != '.')
		i++;
	if (file_path[++i] != 'r')
		quit(minirt, WRONG_EXT_ERR);
	if (file_path[++i] != 't')
		quit(minirt, WRONG_EXT_ERR);
	if (file_path[++i])
		quit(minirt, WRONG_EXT_ERR);
}



void	single_elements_check(t_minirt *minirt, t_scene *scene)
{
	if (scene->nb_amb == 0)
		quit(minirt, MISSING_AMB_ERR);
	else if (scene->nb_amb > 1)
		quit(minirt, TOO_MUCH_AMB_ERR);
	else if (scene->nb_cam == 0)
		quit(minirt, MISSING_CAM_ERR);
	else if (scene->nb_cam > 1)
		quit(minirt, TOO_MUCH_CAM_ERR);
	else if (scene->nb_light == 0)
		quit(minirt, MISSING_LIGHT_ERR);
	else if (scene->nb_light > 1)
		quit(minirt, TOO_MUCH_LIGHT_ERR);
}



