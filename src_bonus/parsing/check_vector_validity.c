#include "minirt.h"

int	is_valid_double(char *s, int *length)
{
	int i;
	int offset;

	i = 0;
	offset = 0;
	if (!s || !s[0])
		return(1);
	if (s[i] == '-')
	{
		i++;
		offset++;
	}
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != '.')
	{
		if ((s[i] == ' ' || s[i] == ',' || s[i] == '\n') && i - offset < 18)
			return (*length += i, 1);
		else
			return (print_err(__FILE__, LINE, "invalid double, more than 17 significant digits: \n"), print_until(s, s[i]), 0);
	}
	i++;
	offset++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (i - offset < 18)
		return(*length += i, 1);
	return(print_err(__FILE__, LINE, "invalid double, more than 17 significant digits: \n"), print_until(s, s[i]), 0);
}

int	is_valid_vector(char *s, int *length)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (e < 3)
	{
		if (!is_valid_double(s + i, length))
			return (0);
		i += *length;
		*length = 0;
		if (e != 2 && s[i] != ',')
			return (0);
		if (e != 2)
			i++;
		e++;
	}
	return (*length = i, 1);
}
