
#include "minirt.h"

void	check_characters_validity(t_minirt *minirt)
{
	const char	alpha_set[] = "ACLsplcy";
	const char	sign_set[] = " \n	.,-+";
	char		*scene;
	int	i;

	scene = minirt->scene->buffer;
	i = -1;
	while (scene[++i])
	{
		if (scene[i] == '\n')
		{
			while (scene[i] && ft_isspace(scene[i]))
				i++;
			if (!ft_is_char_in_string(alpha_set, scene[i]))
				quit(minirt, SCENE_WRONG_CHAR_ERR);
		}
		char_error_check(minirt, scene[i], alpha_set, sign_set);
		/* check if too much letter contained in alpha set (for example 3 p andonly two l/s)*/
	}
	/* at this point, check with wrong arguments (ie ps instead of sp) */
	/* also check if t*/
}


