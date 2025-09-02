/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:56:18 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:56:19 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "vec3.h"

int	generate_random_int(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

double	generate_random_double(double min, double max)
{
	return (min + (double)rand() / RAND_MAX * (max - min));
}

void	print_err(char *file, int line, char *s)
{
	char	*line_str;

	line_str = ft_itoa(line);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("file: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(", line: ", STDERR_FILENO);
	ft_putstr_fd(line_str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	free(line_str);
}

int	get_max_int(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	get_min_int(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

// return a vector (w = 0), set w to 1 for a point
t_vec3	ato_vec3(char *s, int *cursor, t_minirt *minirt)
{
	t_vec3	v;

	if (!s || !s[0])
		quit(minirt, "ato_vec encountered empty str");
	while (ft_isspace(s[*cursor]))
		cursor++;
	v.x = ato_buffer(s + *cursor, cursor, ',');
	v.y = ato_buffer(s + *cursor, cursor, ',');
	v.z = ato_buffer(s + *cursor, cursor, ' ');
	v.w = 0;
	return(v);
}
