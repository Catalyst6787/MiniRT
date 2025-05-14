
#include "minirt.h"

void	check_characters_validity(t_minirt *minirt)
{
	const char	alpha_set[] = "ACLsplcy";
	const char	sign_set[] = " \n	.,-+";
	int	i;

	i = -1;
	while (minirt->scene->buffer[++i])
	{
		if (minirt->scene->buffer[i] == '\n')
		{
			while (minirt->scene->buffer[i] && ft_isspace(minirt->scene->buffer[i]))
				i++;
			if (minirt->scene->buffer[i])
				if (!ft_is_char_in_string(alpha_set, minirt->scene->buffer[i]))
					quit(minirt, SCENE_WRONG_CHAR_ERR);
		}
		if (!minirt->scene->buffer[i])
			break ;
		char_error_check(minirt, minirt->scene->buffer[i], alpha_set, sign_set);
		/* check if too much letter contained in alpha set (for example 3 p andonly two l/s)*/
	}
	/* at this point, check with wrong arguments (ie ps instead of sp) */
	/* also check if t*/
}


