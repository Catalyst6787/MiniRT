/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:50:26 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/03 17:50:27 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	start_render(t_minirt *minirt)
{
	clock_t		t;

	if (MULTI_THREADING)
		return (start_threads(minirt));
	t = clock();
	render_scene(minirt);
	t = clock() - t;
	printf("Scene rendered in %f seconds\n", ((double)t) / CLOCKS_PER_SEC);
	return (0);
}
