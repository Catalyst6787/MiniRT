/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:49:34 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/13 14:23:45 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_all(char **tab, size_t j)
{
	while (j > 0)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
	return (NULL);
}

static size_t	ft_cwords(char const *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_nextword(char const *s, char c, int i)
{
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_wordlen(char const *s, char c, int i)
{
	size_t	j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tab = malloc((ft_cwords(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = ft_nextword(s, c, i);
	while (s[i] && j < ft_cwords(s, c))
	{
		tab[j] = malloc(ft_wordlen(s, c, i) + 1 * sizeof(char));
		if (!tab[j])
			return (free_all(tab, j));
		ft_strlcpy(tab[j], s + i, ft_wordlen(s, c, i) + 1);
		j++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
/*
int	main(void)
{
	ft_split("split three words", ' ');
	return (0);
}
*/
