
#include "minirt.h"

void	check_file_name(t_minirt *minirt, char *file_path)
{
	if (!ft_is_char_in_string(file_path, '.'))
	{
		quit(minirt, EXT_MISSING_ERR);
	}
	/* check extension */
}

void	check_data_validity(t_minirt *minirt)
{
	(void)minirt;
	/* check if data if valid (for example a color value of 300 is not valid) */

}

void	char_error_check(t_minirt *minirt,
							char c,
							const char *alpha_set,
							const char *sign_set)
{
	if (ft_isalpha(c)
		&& !ft_is_char_in_string(alpha_set, c))
	{
		quit(minirt, CHAR_ERR);
	}
	else if (!ft_isalpha(c)
		&& !ft_is_char_in_string(sign_set, c)
		&& !ft_isdigit(c))
	{
		quit(minirt, CHAR_ERR);
	}
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



