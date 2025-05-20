
#include "minirt.h"


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

void	check_each_lines(t_minirt *minirt, char *buffer)
{
	int		i;
	char	c;

	i = 0;
	while (ft_isspace(buffer[i]))
		i++;
	c = buffer[i++];
	while (buffer[i])
	{
		if (buffer[i] == c)
		{
			quit(minirt, CHAR_DOUBLE);
		}
		if (buffer[i] == '\n' && !ft_isspace(buffer[i]) && !ft_isspace(buffer[i + 1]))
		{
			while (buffer[i] || ft_isspace(buffer[i]))
				i++;
			c = buffer[i++];
		}
		i++;
	}
}

void	check_object_format(t_minirt *minirt, char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
	{
		if ((buffer[i] == 's' && buffer[i + 1] != 'p')
			|| (buffer[i] == 'p' && buffer[i + 1] != 'l')
			|| (buffer[i] == 'c' && buffer[i + 1] != 'y')
			|| ((buffer[i] == 'C' || buffer[i] == 'L'
			|| buffer[i] == 'A')  && buffer[i + 1] != ' '))
			quit(minirt, CHAR_ERR);
	}
}

void	check_characters_validity(t_minirt *minirt)
{
	const char	alpha_set[] = "ACLsplcy";
	const char	sign_set[] = " \n	.,-+";
	int	i;

	i = -1;
	if (!minirt->scene->buffer[0])
		return ;
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
		/* check if too much letter contained in alpha set (for example 3 p and only two l/s)*/
	}
	/* check for coments (#) */
	check_each_lines(minirt, minirt->scene->buffer);
	/* at this point, check with wrong arguments (ie ps instead of sp) */
}

