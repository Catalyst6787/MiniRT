#include "minirt.h"

int	count_char_whithout_comments(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '#')
			while (buffer[i] && buffer[i] != '\n')
				i++;
		i++;
		count++;
	}
	return (count);
}

void	strcpy_filter_comments(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
	{
		if (s2[i] == '#')
			while (s2[i] && s2[i] != '\n')
				i++;
		s1[j] = s2[i];
		i++;
		j++;
	}
	s1[j] = '\0';
}

char	*str_dup_no_tab(char *src)
{
	int		len;
	char	*nstr;
	int		i;

	i = 0;
	len = ft_strlen(src);
	nstr = (char *)malloc(sizeof(*src) * (len + 1));
	if (!nstr)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '\t')
			nstr[i] = ' ';
		else
			nstr[i] = src[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	*str_dedup_sp(char *src)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return (NULL);
	ft_memset(res, 0, sizeof(char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		if (src[i] == ' ' && (src[i + 1] == ' ' || src[i + 1] == '\n'))
			i++;
		else
			res[j++] = src[i++];
	}
	return (res);
}
