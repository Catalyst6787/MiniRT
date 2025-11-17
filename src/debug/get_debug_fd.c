/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_debug_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:50:46 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:50:47 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_debug_fd(void)
{
	static int	fd = -1;

	if (fd == -1)
	{
		fd = open("./log/debug.log", O_CREAT | O_RDWR | O_TRUNC, 0664);
		printf("Debug log file created\n");
	}
	return (fd);
}
