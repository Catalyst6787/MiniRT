/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:13:58 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 17:21:24 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_sphere(t_object *object)
{
	if (!object)
		return ;
	free_and_null((void **)&object);
}

int	free_render(t_render *render)
{
	free(render->inter_list.inters);
	free(render->shadow_list.inters);
	return (0);
}
