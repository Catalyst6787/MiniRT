/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:29:52 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 22:29:53 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	has_object_type(char *s, int *i, int *length)
{
	int	e;

	e = 0;
	while (s && s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!ft_isalpha(s[*i]) || !ft_isalpha(s[*i + 1]))
		return (0);
	*i += 2;
	if (!ft_isspace(s[*i]))
		return (0);
	*i += 1;
	while (e < 4)
	{
		if (!is_valid_vector(s + *i, length))
			return (0);
		*i += *length;
		*length = 0;
		if (!ft_isspace(s[*i]))
			return (0);
		*i += 1;
		e++;
	}
	return (1);
}

int	is_valid_material(char *s, int *i, int *length)
{
	int	e;

	e = 0;
	while (e < 4)
	{
		if (!is_valid_double(s + *i, length))
			return (0);
		*i += *length;
		*length = 0;
		if (e != 3 && !ft_isspace(s[*i]))
			return (0);
		if (e != 3)
			*i += 1;
		e++;
	}
	return (1);
}

int	is_valid_shearing(char *s, int *i, int *length)
{
	int	e;

	e = 0;
	while (e < 6)
	{
		if (!is_valid_double(s + *i, length))
			return (0);
		*i += *length;
		*length = 0;
		if (e != 5 && s[*i] != ',')
		{
			printf("s[%d] = %c (%d)\n", *i - 1, s[*i - 1], s[*i - 1]);
			printf("s[%d] = %c (%d)\n", *i, s[*i], s[*i]);
			printf("s[%d] = %c (%d)\n", *i + 1, s[*i + 1], s[*i + 1]);
			return (0);
		}
		if (e != 5)
			*i += 1;
		e++;
	}
	return (1);
}

int	is_valid_object(char *s)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	if (!has_object_type(s, &i, &length))
		return (0);
	if (!is_valid_material(s, &i, &length))
		return (0);
	if (s[i] == '\n' || (s[i] == ' ' && s[i + 1] == '\n'))
		return (1);
	else if (!ft_isspace(s[i]))
		return (0);
	i++;
	if (!is_valid_shearing(s, &i, &length))
		return (0);
	if (s[i] == '\n' || (s[i] == ' ' && s[i + 1] == '\n'))
		return (1);
	return (0);
}
