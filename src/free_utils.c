/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:55:54 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:55:55 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_and_null(void	**ptr)
{
	free(*ptr);
	ptr = NULL;
}

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

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
}
