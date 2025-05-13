/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_in_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:07:45 by alvan-de          #+#    #+#             */
/*   Updated: 2025/05/14 00:09:17 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * To know if a char is present in a string, should be renamed, isnt it ?
 * @param s a string
 * @param c a char
 * @return - 1 if c is in s
 *
 * @return - 0 if c isn't in s
 * @note can be used to see if a char is in a charset !!!
 */
int	ft_is_char_in_string(const char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}
